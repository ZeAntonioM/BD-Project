CREATE TRIGGER mais_5_estrangeiros
AFTER INSERT ON CONVOCATORIA
BEGIN
	SELECT CASE WHEN
		(SELECT count(*)
		FROM CONVOCATORIA c JOIN JOGADOR j JOIN PESSOA p
		ON (c.idJogador = j.idPessoa AND j.idPessoa = p.idPessoa)
		WHERE c.idJogo = NEW.idJogo
		AND j.idEquipa 
		AND p.nacionalidade NOT LIKE 'Brasil') > 5
	THEN
		RAISE(ABORT, 'Mais do que 5 jogadores estrangeiros convocados para uma equipa só')
	END;
END;
