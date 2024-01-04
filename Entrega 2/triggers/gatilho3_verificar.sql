/* Criar a substituição inicial */
INSERT INTO "EVENTO" VALUES (10356, 1, 150, "74");
INSERT INTO "SUBSTITUICAO" VALUES (10356, 154);

/* Esta substituição passará, pois são jogadores distintos da primeira */
INSERT INTO "EVENTO" VALUES (10357, 1, 151, "78");
INSERT INTO "SUBSTITUICAO" VALUES (10357, 152);

/* Esta lançará a mensagem de erro, pois o jogador 150 já foi substiuído no jogo 1 */
INSERT INTO "EVENTO" VALUES (10358, 1, 157, "83");
INSERT INTO "SUBSTITUICAO" VALUES (10358, 150);