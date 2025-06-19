package com.example.family_history_system.entity;

import lombok.Data;

@Data
public class Event {
    private Integer memberId;
    private String eventDate;
    private String eventType;
    private String eventDescription;
    private String eventFile;
}
