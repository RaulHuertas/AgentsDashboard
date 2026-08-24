---
name: agent-monitor
description: Updates the round display with information about the agent
license: MIT
metadata:
  author: Raul Huertas
  version: "1.0"


# Description
Updates the round display with the status of the agent

## When to use this skill
- When a prompt starts its processing, call 'scripts/updateState.ps1' with the name of the model as first argument and '1' as the second argument
- When a prompt finishes its processing, call 'scripts/updateState.ps1' with the name of the model as first argument and '0' as the second argument


## Available scripts
- **`scripts/check.ps1`** — Call at startup
- **`scripts/updateStatus.ps1`** — called at the start and end of prompt processing

## Workflow
- When a prompt starts its processing, call 'scripts/updateState.ps1' with the name of the model as first argument and '1' as the second argument
- When a prompt starts finishes its processing, call 'scripts/updateState.ps1' with the name of the model as first argument and '0' as the second argument




---