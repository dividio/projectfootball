CREATE TABLE PF_COMPETITION_PHASES
(
  N_ORDER INTEGER
  ,X_COMPETITION_PHASE INTEGER PRIMARY KEY AUTOINCREMENT
  ,S_COMPETITION_PHASE TEXT
  ,X_FK_COMPETITION INTEGER
);

CREATE TABLE PF_MATCHES
(
  X_FK_SEASON INTEGER
  ,X_FK_COMPETITION_PHASE INTEGER
  ,X_FK_TEAM_AWAY INTEGER
  ,D_MATCH TEXT
  ,X_MATCH INTEGER PRIMARY KEY AUTOINCREMENT
  ,L_PLAYED TEXT
  ,X_FK_TEAM_HOME INTEGER
);

CREATE TABLE PF_GAME_OPTIONS
(
  S_CATEGORY TEXT
  ,X_OPTION INTEGER PRIMARY KEY AUTOINCREMENT
  ,S_VALUE TEXT
  ,S_ATTRIBUTE TEXT
);

CREATE TABLE PF_COMPETITIONS_BY_SEASON
(
  X_FK_SEASON INTEGER
  ,X_COMPETITION_BY_SEASON INTEGER PRIMARY KEY AUTOINCREMENT
  ,D_END_COMPETITION TEXT
  ,X_FK_COMPETITION INTEGER
  ,D_BEGIN_COMPETITION TEXT
);

CREATE TABLE PF_TEAMS_BY_COMPETITIONS
(
  X_FK_COMPETITION_BY_SEASON INTEGER
  ,X_TEAM_BY_COMPETITION INTEGER PRIMARY KEY AUTOINCREMENT
  ,X_FK_TEAM INTEGER
);

CREATE TABLE PF_SEASONS
(
  X_SEASON INTEGER PRIMARY KEY AUTOINCREMENT
  ,N_YEAR INTEGER
  ,S_SEASON TEXT
);

CREATE TABLE PF_CONFEDERATIONS
(
  X_CONFEDERATION INTEGER PRIMARY KEY AUTOINCREMENT
  ,S_CONFEDERATION TEXT
  ,S_LOGO TEXT
);

CREATE TABLE PF_TEAM_PLAYER_CONTRACTS
(
  D_BEGIN TEXT
  ,X_TEAM_PLAYER_CONTRACT INTEGER PRIMARY KEY AUTOINCREMENT
  ,D_END TEXT
  ,X_FK_TEAM_PLAYER INTEGER
  ,N_LINEUP_ORDER INTEGER
  ,X_FK_TEAM INTEGER
);

CREATE TABLE PF_GOALS
(
  X_FK_TEAM_PLAYER_SCORER INTEGER
  ,X_GOAL INTEGER PRIMARY KEY AUTOINCREMENT
  ,L_OWN_GOAL TEXT
  ,X_FK_TEAM_SCORER INTEGER
  ,X_FK_MATCH INTEGER
  ,N_MINUTE INTEGER
);

CREATE TABLE PF_TEAM_PLAYERS
(
  N_KICK_POWER INTEGER
  ,N_VELOCITY INTEGER
  ,X_TEAM_PLAYER INTEGER PRIMARY KEY AUTOINCREMENT
  ,S_SHORT_NAME TEXT
  ,S_NAME TEXT
  ,X_FK_COUNTRY INTEGER
);

CREATE TABLE PF_COUNTRIES
(
  X_FK_CONFEDERATION INTEGER
  ,S_FLAG TEXT
  ,S_CAPITAL TEXT
  ,S_COUNTRY TEXT
  ,X_COUNTRY INTEGER PRIMARY KEY AUTOINCREMENT
  ,S_SHORT_NAME TEXT
);

CREATE TABLE PF_COMPETITIONS
(
  S_COMPETITION TEXT
  ,D_FOUNDATION TEXT
  ,X_COMPETITION INTEGER PRIMARY KEY AUTOINCREMENT
  ,X_FK_COUNTRY INTEGER
);

CREATE TABLE PF_TEAMS
(
  S_LOGO TEXT
  ,X_TEAM INTEGER PRIMARY KEY AUTOINCREMENT
  ,S_TEAM TEXT
  ,N_BUDGET INTEGER
  ,S_SHORT_NAME TEXT
  ,X_FK_COUNTRY INTEGER
);
