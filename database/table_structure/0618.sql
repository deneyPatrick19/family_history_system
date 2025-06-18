-- `system`.`member` definition

CREATE TABLE `member` (
  `id` varchar(15) NOT NULL,
  `familyTableId` varchar(15) NOT NULL,
  `name` varchar(50) DEFAULT NULL,
  `gender` varchar(5) DEFAULT NULL,
  `birthdate` date DEFAULT NULL,
  `deathdate` date DEFAULT NULL,
  `icon` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.`user` definition

CREATE TABLE `user` (
  `username` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `password` varchar(20) DEFAULT NULL,
  `id` varchar(15) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.event definition

CREATE TABLE `event` (
  `memberId` varchar(15) NOT NULL,
  `eventDate` date DEFAULT NULL,
  `evnetType` varchar(15) DEFAULT NULL,
  `eventDescription` varchar(50) DEFAULT NULL,
  `eventfile` varchar(50) DEFAULT NULL,
  KEY `Event_member_FK` (`memberId`),
  CONSTRAINT `Event_member_FK` FOREIGN KEY (`memberId`) REFERENCES `member` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.relationship definition

CREATE TABLE `relationship` (
  `memberId1` varchar(15) NOT NULL,
  `memberId2` varchar(15) NOT NULL,
  `relation` varchar(15) DEFAULT NULL,
  PRIMARY KEY (`memberId1`,`memberId2`),
  KEY `relationship_member_FK_1` (`memberId2`),
  CONSTRAINT `relationship_member_FK` FOREIGN KEY (`memberId1`) REFERENCES `member` (`id`),
  CONSTRAINT `relationship_member_FK_1` FOREIGN KEY (`memberId2`) REFERENCES `member` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;