#!/bin/bash
ERRORS=(
    "buffer_overflow"
    "core_dumped"
    "deadlock"
    "memory_leak"
    "race_condition"
    "segmentation_fault"
    "stack_overflow"
)

while true; do
    clear
    echo "=== Error Emulator ==="
    for i in "${!ERRORS[@]}"; do
        printf "  %2d) %s\n" "$((i+1))" "${ERRORS[$i]}"
    done
    echo "   q) Sair"
    read -p "Sua escolha: " ESCOLHA
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
                    echo "=== Executando '$EXECUTAVEL' ==="
                    echo
                    ./"$EXECUTAVEL"
                else
                    echo "Opção inválida."
                fi
            else
                echo "Opção inválida."
                echo
            fi
            read -p "Pressione Enter para continuar..."
            ;;
    esac
done