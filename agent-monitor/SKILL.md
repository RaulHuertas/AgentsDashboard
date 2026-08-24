---
name: agent-monitor
description: Updates the round display with the status of the agent
license: MIT
metadata:
  author: Raul Huertas
  version: "1.0"

---

# Description
Updates the round display with the status of the agent.

## When to use this skill
- When a prompt starts processing, call `scripts/updateStatus.ps1` with the model name as the first argument and `1` as the second argument.
- When a prompt finishes processing, call `scripts/updateStatus.ps1` with the model name as the first argument and `0` as the second argument.


## Available scripts
- **`scripts/check.ps1`** - Call at startup of the agent, no arguments. Show the result to the user.
- **`scripts/updateStatus.ps1`** - Call at the start and end of prompt processing.


