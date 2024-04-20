# !/bin/bash

TOTAL=$(find srcs srcs/token_runner srcs/x_funcs srcs/builtins -type f -name "*.c" | wc -l)
COMPILED=0

TERMINAL_WIDTH=$(tput cols)
MAX_BAR_LENGTH=$((TERMINAL_WIDTH / 2 - 10))

for file in $(find srcs srcs/token_runner srcs/x_funcs srcs/builtins -type f -name "*.c"); do
    sleep 0.1
    ((COMPILED++))
    PROGRESS_BAR=""
    FILLED_LENGTH=$((COMPILED * MAX_BAR_LENGTH / TOTAL))
    for ((i = 0; i < FILLED_LENGTH; i++)); do
        PROGRESS_BAR+="█"
    done
    for ((i = FILLED_LENGTH; i < MAX_BAR_LENGTH; i++)); do
        PROGRESS_BAR+=" "
    done
    printf "\e[KProgress: [%s] %d/%d files compiled\r" "$PROGRESS_BAR" "$COMPILED" "$TOTAL"
done
