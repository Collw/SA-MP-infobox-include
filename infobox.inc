/*
 * ----------------------------------------------------------------------
 *                          InfoBox Include
 *                             by Collw
 *                       V 1.0 - Build 1.09.865
 *
 * Descrição: Este include fornece funcionalidades para criar e gerenciar
 *            InfoBoxes (Notificações em TextDraws) no SA-MP.
 * Link do GitHub: https://github.com/Collw
 * ----------------------------------------------------------------------
 */
#if defined INFOBOX_INC
	#endinput
 #endif
#define INFOBOX_INC

#include <a_samp>

// Definição do máximo de TextDraws permitidos
#define MAX_INFOBOX 10
#define MAX_PLAYERS 1000

// Declaração das variáveis globais
new Text:infoboxTD[MAX_INFOBOX];  // Armazena os TextDraws
new currentTextDraw = 0;          // Contador de TextDraws atualmente em uso

// Função para criar a InfoBox
public CreateInfoBox(playerid, text[])
{
    if (currentTextDraw >= MAX_INFOBOX) return; // Limita a 10 TextDraws

    // Define as coordenadas para o TextDraw
    new Float:x = 9.0;   // Coordenada X
    new Float:y = 307.0 - (currentTextDraw * 12.0); // Ajuste para cada novo TextDraw

    // Cria o TextDraw
    infoboxTD[currentTextDraw] = TextDrawCreate(x, y, text);
    TextDrawFont(infoboxTD[currentTextDraw], 1);
    TextDrawLetterSize(infoboxTD[currentTextDraw], 0.170833, 0.650000);
    TextDrawTextSize(infoboxTD[currentTextDraw], 204.500000, 17.000000);
    TextDrawSetOutline(infoboxTD[currentTextDraw], 1);
    TextDrawSetShadow(infoboxTD[currentTextDraw], 0);
    TextDrawAlignment(infoboxTD[currentTextDraw], 1);
    TextDrawColor(infoboxTD[currentTextDraw], 1687547391); // Cor RGBA
    TextDrawBackgroundColor(infoboxTD[currentTextDraw], -1); // Sem cor de fundo
    TextDrawBoxColor(infoboxTD[currentTextDraw], -1);        // Sem cor de caixa
    TextDrawUseBox(infoboxTD[currentTextDraw], 1);
    TextDrawSetProportional(infoboxTD[currentTextDraw], 1);
    TextDrawSetSelectable(infoboxTD[currentTextDraw], 0);

    // Exibe o TextDraw para o jogador
    TextDrawShowForPlayer(playerid, infoboxTD[currentTextDraw]);
    PlayerPlaySound(playerid, 6401, 0.0, 0.0, 0.0); // Som de notificação
    
    // Agenda a destruição do TextDraw após 7 segundos
    SetTimer("DestroyInfoBox", 7000, false);

    currentTextDraw++; // Incrementa o índice de TextDraws
}

// Função para destruir o TextDraw mais antigo
public DestroyInfoBox()
{
    if (currentTextDraw > 0) {
        currentTextDraw--; // Decrementa o índice
        
        // Destroi o TextDraw para todos os jogadores conectados
        for (new playerId = 0; playerId < MAX_PLAYERS; playerId++) {
            if (IsPlayerConnected(playerId)) {
                TextDrawDestroy(infoboxTD[currentTextDraw]);
            }
        }
    }
	
}
