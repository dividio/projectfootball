CREATE VIEW PF_TEAM_AVERAGES
AS
SELECT X_TEAM,
       AVG(DEFENSE) AS N_DEFENSE,
       AVG(ATTACK)  AS N_ATTACK,
       AVG(TOTAL)   AS N_TOTAL
FROM
(
    SELECT TPC.X_FK_TEAM AS X_TEAM,
           TPA.N_DEFENSE AS DEFENSE,
           TPA.N_ATTACK  AS ATTACK,
           TPA.N_TOTAL   AS TOTAL
    FROM PF_TEAM_PLAYER_AVERAGES TPA
         JOIN PF_TEAM_PLAYER_CONTRACTS TPC
         ON TPC.X_FK_TEAM_PLAYER=TPA.X_TEAM_PLAYER
    WHERE D_BEGIN<=CURRENT_TIMESTAMP
    AND  (D_END IS NULL OR D_END>CURRENT_TIMESTAMP)
    AND   N_LINEUP_ORDER>=1 AND N_LINEUP_ORDER<=11
)
GROUP BY X_TEAM
;
