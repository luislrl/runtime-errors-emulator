#!/bin/bash

TOP_MARGIN=6
BLUE='\033[36m'
NC='\033[0m'

read -r -d '' asciiart <<'EOT'
 _  .-')                   .-') _  .-') _          _   .-')       ('-.           ('-.  _  .-')  _  .-')               _  .-')   
( \( -O )                 ( OO ) )(  OO) )        ( '.( OO )_   _(  OO)        _(  OO)( \( -O )( \( -O )             ( \( -O )  
 ,------. ,--. ,--.   ,--./ ,--,' /     '._ ,-.-') ,--.   ,--.)(,------.      (,------.,------. ,------.  .-'),-----. ,------.  
 |   /`. '|  | |  |   |   \ |  |\ |'--...__)|  |OO)|   `.'   |  |  .---'       |  .---'|   /`. '|   /`. '( OO'  .-.  '|   /`. ' 
 |  /  | ||  | | .-') |    \|  | )'--.  .--'|  |  \|         |  |  |           |  |    |  /  | ||  /  | |/   |  | |  ||  /  | | 
 |  |_.' ||  |_|( OO )|  .     |/    |  |   |  |(_/|  |'.'|  | (|  '--.       (|  '--. |  |_.' ||  |_.' |\_) |  |\|  ||  |_.' | 
 |  .  '.'|  | | `-' /|  |\    |     |  |  ,|  |_.'|  |   |  |  |  .--'        |  .--' |  .  '.'|  .  '.'  \ |  | |  ||  .  '.' 
 |  |\  \('  '-'(_.-' |  | \   |     |  | (_|  |   |  |   |  |  |  `---.       |  `---.|  |\  \ |  |\  \    `'  '-'  '|  |\  \  
 `--' '--' `-----'    `--'  `--'     `--'   `--'   `--'   `--'  `------'       `------'`--' '--'`--' '--'     `-----' `--' '--' 
   ('-.  _   .-')                             ('-.     .-') _                _  .-')                                            
 _(  OO)( '.( OO )_                          ( OO ).-.(  OO) )              ( \( -O )                                           
(,------.,--.   ,--.),--. ,--.    ,--.       / . --. //     '._  .-'),-----. ,------.                                           
 |  .---'|   `.'   | |  | |  |    |  |.-')   | \-.  \ |'--...__)( OO'  .-.  '|   /`. '                                          
 |  |    |         | |  | | .-')  |  | OO ).-'-'  |  |'--.  .--'/   |  | |  ||  /  | |                                          
(|  '--. |  |'.'|  | |  |_|( OO ) |  |`-' | \| |_.'  |   |  |   \_) |  |\|  ||  |_.' |                                          
 |  .--' |  |   |  | |  | | `-' /(|  '---.'  |  .-.  |   |  |     \ |  | |  ||  .  '.'                                          
 |  `---.|  |   |  |('  '-'(_.-'  |      |   |  | |  |   |  |      `'  '-'  '|  |\  \                                           
 `------'`--'   `--'  `-----'     `------'   `--' `--'   `--'        `-----' `--' '--'                                                                   
EOT

ERRORS=(
    "buffer_overflow"
    "core_dumped"
    "deadlock"
    "memory_leak"
    "race_condition"
    "segmentation_fault"
    "stack_overflow"
)

visible_len() {
    local line="$1"

    line=$(echo -e "$line" | sed -E 's/\x1B\[[0-9;]*[mK]//g')

    printf "%s" "$line" | wc -m
}

get_max_width() {
    local text="$1"
    local max=0

    while IFS= read -r line; do
        local len
        len=$(visible_len "$line")

        if (( len > max )); then
            max=$len
        fi
    done <<< "$text"

    echo "$max"
}

get_left_padding() {
    local text="$1"
    local terminal_width
    local text_width
    local padding

    terminal_width=$(tput cols)
    text_width=$(get_max_width "$text")

    padding=$(( (terminal_width - text_width) / 2 ))

    if (( padding < 0 )); then
        padding=0
    fi

    echo "$padding"
}

print_with_padding() {
    local text="$1"
    local padding="$2"

    while IFS= read -r line; do
        printf "%*s%b\n" "$padding" "" "$line"
    done <<< "$text"
}

while true; do
    clear

    for ((i = 0; i < TOP_MARGIN; i++)); do
        echo
    done

    PADDING=$(get_left_padding "$asciiart")

    print_with_padding "${BLUE}${asciiart}${NC}" "$PADDING"
    echo

    for i in "${!ERRORS[@]}"; do
        printf "%*s%2d) %s\n" "$PADDING" "" "$((i+1))" "${ERRORS[$i]}"
    done

    printf "%*s q) Sair\n" "$PADDING" ""
    echo

    printf "%*sSua escolha: " "$PADDING" ""
    read -r ESCOLHA
    echo

    case "$ESCOLHA" in
        q|Q)
            break
            ;;
        *)
            if [[ "$ESCOLHA" =~ ^[0-9]+$ ]]; then
                INDEX=$((ESCOLHA-1))

                if [ -n "${ERRORS[$INDEX]}" ]; then
                    EXECUTAVEL="${ERRORS[$INDEX]}"

                    printf "%*s=== Executando '%s' ===\n" "$PADDING" "" "$EXECUTAVEL"
                    echo
                    ./"$EXECUTAVEL"
                else
                    printf "%*sOpção inválida.\n" "$PADDING" ""
                fi
            else
                printf "%*sOpção inválida.\n" "$PADDING" ""
                echo
            fi

            echo
            printf "%*sPressione Enter para continuar..." "$PADDING" ""
            read -r
            ;;
    esac
done