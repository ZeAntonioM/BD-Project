CREATE TRIGGER restricao_substituicao
BEFORE INSERT ON SUBSTITUICAO
WHEN EXISTS(
	SELECT *
	FROM SUBSTITUICAO s JOIN EVENTO e
	ON (s.idEvento = e.idEvento)
	WHERE (
		e.idJogador = NEW.idJogadorSubstituto
		)
	)
BEGIN
	SELECT RAISE(ABORT, 'Jogador substituído não pode voltar ao jogo');
END;
