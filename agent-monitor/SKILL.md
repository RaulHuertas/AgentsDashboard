---
name: agent-monitor
description: Updates the board display with the status of the agent
license: MIT
metadata:
  author: Raul Huertas
  version: "1.0"
---

# Description
Updates the board display with the status of the agent.

## When to use this skill
- At agent startup, call `agent-monitor/scripts/check.ps1` to verify device communication.
- When a prompt starts processing, call `agent-monitor/scripts/updateStatus.ps1` with the agent name as the first argument and `1` as the second argument.
- When a prompt finishes processing, call `agent-monitor/scripts/updateStatus.ps1` with the agent name as the first argument and `0` as the second argument.

Optional arguments:
- `agent-monitor/scripts/check.ps1`: optional first argument for serial port device (defaults to `COM3`).
- `agent-monitor/scripts/updateStatus.ps1`: optional third argument for serial port device (defaults to `COM3`).

Examples:
- Startup check: `pwsh -File agent-monitor/scripts/check.ps1 COM3`
- Start processing: `pwsh -File agent-monitor/scripts/updateStatus.ps1 "gpt-5.3-codex" 1 COM3`
- End processing: `pwsh -File agent-monitor/scripts/updateStatus.ps1 "gpt-5.3-codex" 0 COM3`


## Available scripts
- **`scripts/check.ps1`** - Call at startup of the agent. No required arguments (optional: port device).
- **`scripts/updateStatus.ps1`** - Call at the start and end of prompt processing. Arguments: `<agentName> <working:0|1> [portDevice]`.
