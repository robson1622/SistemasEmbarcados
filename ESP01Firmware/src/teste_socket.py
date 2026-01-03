import socket
import struct
import time
from datetime import datetime

# --- CONFIGURAÇÕES ---
ESP_IP = "192.168.1.106" 
PORT = 23
PASSWORD = b"bwa94/'dp[a]+=d" # Senha exata do seu InfoType.h

# Definições conforme seu InfoType.h
TELEMETRY_TYPE = 0
TERMINAL_TEXT_TYPE = 1

# Condições Meteorológicas
SUM, MOOM, RAIN = 0, 1, 2

# Views do Display
TERMINAL_VIEW = 0
TEMP_VIEW = 1
VENT_VIEW = 2
TERMINAL_TEXT_VIEW = 3

def pack_telemetry(meteo=SUM, view=TEMP_VIEW):
    """Empacota telemetria incluindo meteo_condition e view."""
    # 1. Coleta de dados simulada
    battery_level, fan_speed, temp_proc = 92, 50, 48
    t_clima, t_max, t_min = 25, 30, 18
    now = datetime.now()
    month, day, hour, minute = now.month, now.day, now.hour, now.minute
    day_name = now.strftime("%a").upper()[:3].encode('ascii').ljust(4, b'\0') # "SEG\0"

    # 2. Flags (bitfield): connected, wifi, charging, fan, topbar, screen
    flags = 0b11111111 

    # 3. Definição do Formato (Total: 81 bytes para casar com sizeof(InfoPacket))
    # Password(16s) + Type(B) + TelemetryData(10B + 4s + B + B + B) + Padding(47s)
    # 16 + 1 + 10 + 4 + 1 + 1 + 1 + 47 = 81 bytes
    fmt = "<16sB BBBBBBBBBB4sBBB 47s"
    
    padding = b'\0' * 47 # Preenche o resto da union de 64 bytes
    
    packet = struct.pack(fmt, 
        PASSWORD.ljust(16, b'\0'), TELEMETRY_TYPE,
        battery_level, fan_speed, temp_proc, t_clima, t_max, t_min,
        month, day, hour, minute,
        day_name, flags, meteo, view,
        padding
    )
    return packet

def pack_terminal(text):
    """Empacota texto para o modo terminal (exatamente 81 bytes)."""
    # Password(16s) + Type(B) + TerminalText(64s)
    fmt = "<16sB64s"
    text_encoded = text.encode('ascii')[:64].ljust(64, b'\0')
    return struct.pack(fmt, PASSWORD.ljust(16, b'\0'), TERMINAL_TEXT_TYPE, text_encoded)

def send_to_esp(payload):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.settimeout(3)
            s.connect((ESP_IP, PORT))
            s.sendall(payload)
            print(f"[+] Enviado: {len(payload)} bytes")
    except Exception as e:
        print(f"[!] Erro: {e}")

if __name__ == "__main__":
    print(f"[*] Conectando ao ESP em {ESP_IP}...")
    
    menu = f"""
    {'-'*30}
    CONTROLE DE VIEW (ESP-01)
    {'-'*30}
    0: TERMINAL_VIEW
    1: TEMP_VIEW
    2: VENT_VIEW
    3: TERMINAL_TEXT_VIEW
    
    T: Enviar texto p/ Terminal
    M: Mudar ícone Clima (Ciclo)
    Q: Sair
    {'-'*30}
    """
    print(menu)

    current_meteo = SUM # Inicia com Sol

    while True:
        opcao = input("Selecione a View ou Comando: ").strip().upper()

        if opcao == 'Q':
            print("[*] Encerrando...")
            break

        # Transição entre Views (0, 1, 2 ou 3)
        if opcao in ['0', '1', '2', '3']:
            view_id = int(opcao)
            print(f"[*] Solicitando View {view_id}...")
            # Envia telemetria com a view desejada
            payload = pack_telemetry(meteo=current_meteo, view=view_id)
            send_to_esp(payload)

        # Enviar texto para a tela de texto/terminal
        elif opcao == 'T':
            msg = input("Texto para enviar: ")
            print("[*] Enviando pacote de texto...")
            payload = pack_terminal(msg)
            send_to_esp(payload)

        # Ciclo de ícones de clima (Apenas para teste)
        elif opcao == 'M':
            current_meteo = (current_meteo + 1) % 3
            print(f"[*] Alterando ícone de clima para ID: {current_meteo}")
            payload = pack_telemetry(meteo=current_meteo, view=TEMP_VIEW)
            send_to_esp(payload)

        else:
            print("[!] Opção inválida. Use 0-3, T, M ou Q.")