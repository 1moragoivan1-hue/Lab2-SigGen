#!/bin/bash

# Stop if the build or executable fails.
set -e

CYAN='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ "$#" -lt 2 ]; then
    echo -e "${CYAN}${CYAN}[INFO]${NC}${NC} Usage: ./run.sh <task_number> <module_name> [arguments...]"
    echo -e "${CYAN}${CYAN}[INFO]${NC}${NC} Example: ./run.sh 1 counter"
    exit 1
fi

TASK_NUM=$1
MODULE_NAME=$2
shift 2

TARGET="task${TASK_NUM}_${MODULE_NAME}"
TASK_FOLDER="./build/task${TASK_NUM}"

echo -e "${CYAN}[INFO]${NC} Starting workflow for Task: ${TASK_NUM} | Module: ${MODULE_NAME}"
if [ -f "task${TASK_NUM}/${MODULE_NAME}.py" ]; then
    echo -e "${CYAN}[INFO]${NC} Found Python script for module. Running task${TASK_NUM}/${MODULE_NAME}.py..."
    uv run python "task${TASK_NUM}/${MODULE_NAME}.py"
fi


mkdir -p "$TASK_FOLDER"
# Build the executable.
echo -e "${CYAN}[INFO]${NC} Building CMake target: $TARGET..."
cmake --build build --target "$TARGET"

# Run inside the task's build folder so the VCD is written there.
echo -e "${CYAN}[INFO]${NC} Changing directory to $TASK_FOLDER..."
cd "$TASK_FOLDER"

echo -e "${CYAN}[INFO]${NC} Running simulation executable: ./${TARGET} $*"
"./${TARGET}" "$@"

# Open the generated waveform.
echo -e "${CYAN}[INFO]${NC} Simulation complete. Opening waveform ${MODULE_NAME}_tb.vcd in GTKWave..."
gtkwave "${MODULE_NAME}_tb.vcd"

echo -e "${GREEN}[INFO]${NC} Done!"
