#include "ATCommandScanner.h"

#include <string.h>
#include <stdlib.h>

#include "AgentsDashboard.h"

static Stream* g_serialPort = nullptr;

static const size_t AT_BUFFER_SIZE = 64;
static char g_lineBuffer[AT_BUFFER_SIZE];
static size_t g_lineLength = 0;

static void sendOk() {
    if (g_serialPort != nullptr) {
        g_serialPort->println("OK");
    }
}

static void sendError(const char* reason) {
    if (g_serialPort != nullptr) {
        g_serialPort->print("ERROR:");
        g_serialPort->println(reason);
    }
}

static bool parseIndexAndRest(const char* payload, int* outIndex, const char** outRest) {
    if (payload == nullptr || outIndex == nullptr || outRest == nullptr) {
        return false;
    }

    char* endPtr = nullptr;
    long parsedIndex = strtol(payload, &endPtr, 10);
    if (endPtr == payload || endPtr == nullptr || *endPtr != ',') {
        return false;
    }

    if (parsedIndex < 0 || parsedIndex >= NSTATUS) {
        return false;
    }

    *outIndex = (int)parsedIndex;
    *outRest = endPtr + 1;
    return true;
}

static void handleUpdateAgentName(const char* payload) {
    int index = -1;
    const char* name = nullptr;
    if (!parseIndexAndRest(payload, &index, &name)) {
        sendError("invalid_name_payload");
        return;
    }

    setStatusCircleLabel((uint8_t)index, name);
    sendOk();
}

static void handleUpdateAgentStatus(const char* payload) {
    int index = -1;
    const char* statusText = nullptr;
    if (!parseIndexAndRest(payload, &index, &statusText)) {
        sendError("invalid_status_payload");
        return;
    }

    if (statusText[0] == '\0' || statusText[1] != '\0') {
        sendError("status_must_be_0_or_1");
        return;
    }

    if (statusText[0] == '0') {
        setStatusCircleAnimation((uint8_t)index, false);
        sendOk();
        return;
    }

    if (statusText[0] == '1') {
        setStatusCircleAnimation((uint8_t)index, true);
        sendOk();
        return;
    }

    sendError("status_must_be_0_or_1");
}

static void handlePlaceAgentStatus(char* payload) {
    if (payload == nullptr || payload[0] == '\0') {
        sendError("invalid_place_status_payload");
        return;
    }

    char* separator = strchr(payload, ',');
    if (separator == nullptr) {
        sendError("invalid_place_status_payload");
        return;
    }

    *separator = '\0';
    const char* name = payload;
    const char* statusText = separator + 1;

    if (name[0] == '\0') {
        sendError("invalid_place_status_payload");
        return;
    }

    if (statusText[0] == '\0' || statusText[1] != '\0') {
        sendError("status_must_be_0_or_1");
        return;
    }

    if (statusText[0] != '0' && statusText[0] != '1') {
        sendError("status_must_be_0_or_1");
        return;
    }

    bool working = (statusText[0] == '1');
    if (!updateOrPlaceAgentStatus(name, working)) {
        sendError("cannot_place_agent_status");
        return;
    }

    sendOk();
}

static void processCommand(char* line) {
    if (line == nullptr || line[0] == '\0') {
        return;
    }

    if (strcmp(line, "AT") == 0) {
        if (g_serialPort != nullptr) {
            g_serialPort->println("Agent Monitor, by Raul Huertas");
        }
        sendOk();
        return;
    }

    static const char* UPDATE_NAME_PREFIX = "AT+UpdateAgentName=";
    static const size_t UPDATE_NAME_PREFIX_LEN = 19;
    if (strncmp(line, UPDATE_NAME_PREFIX, UPDATE_NAME_PREFIX_LEN) == 0) {
        handleUpdateAgentName(line + UPDATE_NAME_PREFIX_LEN);
        return;
    }

    static const char* UPDATE_STATUS_PREFIX = "AT+UpdateAgentStatus=";
    static const size_t UPDATE_STATUS_PREFIX_LEN = 21;
    if (strncmp(line, UPDATE_STATUS_PREFIX, UPDATE_STATUS_PREFIX_LEN) == 0) {
        handleUpdateAgentStatus(line + UPDATE_STATUS_PREFIX_LEN);
        return;
    }

    static const char* PLACE_STATUS_PREFIX = "AT+PlaceAgentStatus=";
    static const size_t PLACE_STATUS_PREFIX_LEN = 20;
    if (strncmp(line, PLACE_STATUS_PREFIX, PLACE_STATUS_PREFIX_LEN) == 0) {
        handlePlaceAgentStatus(line + PLACE_STATUS_PREFIX_LEN);
        return;
    }

    sendError("unknown_command");
}

void initATCommandScanner(Stream& serialPort) {
    g_serialPort = &serialPort;
    g_lineLength = 0;
    g_lineBuffer[0] = '\0';
}

void pollATCommandScanner() {
    if (g_serialPort == nullptr) {
        return;
    }

    while (g_serialPort->available() > 0) {
        int incoming = g_serialPort->read();
        if (incoming < 0) {
            return;
        }

        char c = (char)incoming;
        if (c == '\r' || c == '\n') {
            if (g_lineLength > 0) {
                g_lineBuffer[g_lineLength] = '\0';
                processCommand(g_lineBuffer);
                g_lineLength = 0;
                g_lineBuffer[0] = '\0';
            }
            continue;
        }

        if (g_lineLength >= (AT_BUFFER_SIZE - 1)) {
            g_lineLength = 0;
            g_lineBuffer[0] = '\0';
            sendError("command_too_long");
            continue;
        }

        g_lineBuffer[g_lineLength] = c;
        g_lineLength++;
    }
}
