CREATE TRIGGER mais_23_convocatoria
AFTER INSERT ON CONVOCATORIA
BEGIN
	SELECT CASE WHEN
		(SELECT COUNT(*) AS mycount
		FROM CONVOCATORIA c JOIN JOGADOR j
		ON (c.idJogador = j.idPessoa)
		WHERE c.idJogo = NEW.idJogo
		AND j.idEquipa = (
				SELECT idEquipa
				FROM JOGADOR jo
				WHERE (jo.idPessoa = NEW.idJogador)
				)
		) > 23
		
	THEN
		RAISE(ABORT, 'Mais do que 23 jogadores convocados para uma equipa só')
	END;
END;

