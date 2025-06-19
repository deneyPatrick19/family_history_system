package com.example.family_history_system.entity;

import lombok.Data;

@Data
public class FamilyTable {
    private Integer id;
    private Integer memberID;
    private String tableName;
    private String content;
    private String establishTime;
}
