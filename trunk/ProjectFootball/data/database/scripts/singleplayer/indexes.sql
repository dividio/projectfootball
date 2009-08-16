CREATE INDEX PF_COMPETITION_PHASES_X_COMPETITION_PHASE ON PF_COMPETITION_PHASES (X_COMPETITION_PHASE);
CREATE INDEX PF_COMPETITION_PHASES_X_FK_COMPETITION ON PF_COMPETITION_PHASES (X_FK_COMPETITION);
CREATE INDEX PF_MATCHES_X_FK_SEASON ON PF_MATCHES (X_FK_SEASON);
CREATE INDEX PF_MATCHES_X_FK_COMPETITION_PHASE ON PF_MATCHES (X_FK_COMPETITION_PHASE);
CREATE INDEX PF_MATCHES_X_FK_TEAM_AWAY ON PF_MATCHES (X_FK_TEAM_AWAY);
CREATE INDEX PF_MATCHES_X_MATCH ON PF_MATCHES (X_MATCH);
CREATE INDEX PF_MATCHES_X_FK_TEAM_HOME ON PF_MATCHES (X_FK_TEAM_HOME);
CREATE INDEX PF_GAME_OPTIONS_X_OPTION ON PF_GAME_OPTIONS (X_OPTION);
CREATE INDEX PF_COMPETITIONS_BY_SEASON_X_FK_SEASON ON PF_COMPETITIONS_BY_SEASON (X_FK_SEASON);
CREATE INDEX PF_COMPETITIONS_BY_SEASON_X_COMPETITION_BY_SEASON ON PF_COMPETITIONS_BY_SEASON (X_COMPETITION_BY_SEASON);
CREATE INDEX PF_COMPETITIONS_BY_SEASON_X_FK_COMPETITION ON PF_COMPETITIONS_BY_SEASON (X_FK_COMPETITION);
CREATE INDEX PF_TEAMS_BY_COMPETITIONS_X_FK_COMPETITION_BY_SEASON ON PF_TEAMS_BY_COMPETITIONS (X_FK_COMPETITION_BY_SEASON);
CREATE INDEX PF_TEAMS_BY_COMPETITIONS_X_TEAM_BY_COMPETITION ON PF_TEAMS_BY_COMPETITIONS (X_TEAM_BY_COMPETITION);
CREATE INDEX PF_TEAMS_BY_COMPETITIONS_X_FK_TEAM ON PF_TEAMS_BY_COMPETITIONS (X_FK_TEAM);
CREATE INDEX PF_SEASONS_X_SEASON ON PF_SEASONS (X_SEASON);
CREATE INDEX PF_CONFEDERATIONS_X_CONFEDERATION ON PF_CONFEDERATIONS (X_CONFEDERATION);
CREATE INDEX PF_TEAM_PLAYER_CONTRACTS_X_TEAM_PLAYER_CONTRACT ON PF_TEAM_PLAYER_CONTRACTS (X_TEAM_PLAYER_CONTRACT);
CREATE INDEX PF_TEAM_PLAYER_CONTRACTS_X_FK_TEAM_PLAYER ON PF_TEAM_PLAYER_CONTRACTS (X_FK_TEAM_PLAYER);
CREATE INDEX PF_TEAM_PLAYER_CONTRACTS_X_FK_TEAM ON PF_TEAM_PLAYER_CONTRACTS (X_FK_TEAM);
CREATE INDEX PF_GOALS_X_FK_TEAM_PLAYER_SCORER ON PF_GOALS (X_FK_TEAM_PLAYER_SCORER);
CREATE INDEX PF_GOALS_X_GOAL ON PF_GOALS (X_GOAL);
CREATE INDEX PF_GOALS_X_FK_TEAM_SCORER ON PF_GOALS (X_FK_TEAM_SCORER);
CREATE INDEX PF_GOALS_X_FK_MATCH ON PF_GOALS (X_FK_MATCH);
CREATE INDEX PF_TEAM_PLAYERS_X_TEAM_PLAYER ON PF_TEAM_PLAYERS (X_TEAM_PLAYER);
CREATE INDEX PF_TEAM_PLAYERS_X_FK_COUNTRY ON PF_TEAM_PLAYERS (X_FK_COUNTRY);
CREATE INDEX PF_COUNTRIES_X_FK_CONFEDERATION ON PF_COUNTRIES (X_FK_CONFEDERATION);
CREATE INDEX PF_COUNTRIES_X_COUNTRY ON PF_COUNTRIES (X_COUNTRY);
CREATE INDEX PF_COMPETITIONS_X_FK_COUNTRY ON PF_COMPETITIONS (X_FK_COUNTRY);
CREATE INDEX PF_COMPETITIONS_X_COMPETITION ON PF_COMPETITIONS (X_COMPETITION);
CREATE INDEX PF_TEAMS_X_TEAM ON PF_TEAMS (X_TEAM);
CREATE INDEX PF_TEAMS_X_FK_COUNTRY ON PF_TEAMS (X_FK_COUNTRY);
