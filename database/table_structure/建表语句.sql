-- `system`.`user` definition

CREATE TABLE `user` (
  `username` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `password` varchar(20) DEFAULT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_unique` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.family_table definition

CREATE TABLE `family_table` (
  `id` int NOT NULL AUTO_INCREMENT,
  `table_name` varchar(50) DEFAULT NULL,
  `content` varchar(100) DEFAULT NULL,
  `establish_time` date DEFAULT NULL,
  `user_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `family_table_user_FK` (`user_id`),
  CONSTRAINT `family_table_user_FK` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.`member` definition

CREATE TABLE `member` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `gender` varchar(5) DEFAULT NULL,
  `birthdate` date DEFAULT NULL,
  `deathdate` date DEFAULT NULL,
  `bio` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `family_table_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `member_family_table_FK` (`family_table_id`),
  CONSTRAINT `member_family_table_FK` FOREIGN KEY (`family_table_id`) REFERENCES `family_table` (`id`),
  CONSTRAINT `member_check` CHECK ((`gender` in (_utf8mb4'男',_utf8mb4'女')))
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.relationship definition

CREATE TABLE `relationship` (
  `member_id1` int NOT NULL,
  `member_id2` int NOT NULL,
  `relation` varchar(15) DEFAULT NULL,
  PRIMARY KEY (`member_id1`,`member_id2`),
  KEY `relationship_member_FK_1` (`member_id2`),
  CONSTRAINT `relationship_member_FK` FOREIGN KEY (`member_id1`) REFERENCES `member` (`id`),
  CONSTRAINT `relationship_member_FK_1` FOREIGN KEY (`member_id2`) REFERENCES `member` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- `system`.event definition

CREATE TABLE `event` (
  `member_id` int NOT NULL,
  `event_date` date DEFAULT NULL,
  `event_type` varchar(20) DEFAULT NULL,
  `event_description` varchar(100) DEFAULT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `event_member_FK` (`member_id`),
  CONSTRAINT `event_member_FK` FOREIGN KEY (`member_id`) REFERENCES `member` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;