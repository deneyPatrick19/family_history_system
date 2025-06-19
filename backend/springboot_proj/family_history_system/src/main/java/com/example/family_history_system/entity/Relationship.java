package com.example.family_history_system.entity;

import lombok.Data;

@Data
public class Relationship {
    private Integer memberId1;
    private Integer memberId2;
    private String relation;
}
