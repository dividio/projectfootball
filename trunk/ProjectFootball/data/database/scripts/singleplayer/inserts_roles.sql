INSERT INTO PF_DEMARCATIONS (X_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (1,'Goalkeeper','GK');
INSERT INTO PF_DEMARCATIONS (X_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (2,'Defender','DF');
INSERT INTO PF_DEMARCATIONS (X_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (3,'Midfielder','MF');
INSERT INTO PF_DEMARCATIONS (X_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (4,'Forward','FW');

INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (1,1,'Goalkeeper','GK');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (2,2,'Sweeper','SW');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (3,2,'Left Wingback','LWB');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (4,2,'Right Wingback','RWB');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (5,2,'Left Centre-back','LCB');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (6,2,'Right Centre-back','RCB');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (7,2,'Left Full Back','LFB');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (8,2,'Right Full Back','RFB');

INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (9,3,'Left Centre Midfielder','LCM');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (10,3,'Right Centre Midfielder','RCM');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (11,3,'Left Side Midfielder','LSM');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (12,3,'Right Side Midfielder','RSM');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (13,3,'Defensive Midfielder','DM');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (14,3,'Offensive Midfielder','OM');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (15,3,'Left Winger','LWG');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (16,3,'Right Winger','RWG');

INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (17,4,'Centre Forward','CF');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (18,4,'Left Striker','LST');
INSERT INTO PF_ROLES (X_ROLE,X_FK_DEMARCATION,S_NAME,S_SHORT_NAME) VALUES (19,4,'Right Striker','RST');