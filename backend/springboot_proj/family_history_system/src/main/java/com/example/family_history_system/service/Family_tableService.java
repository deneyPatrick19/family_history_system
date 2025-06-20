package com.example.family_history_system.service;

import com.example.family_history_system.entity.Family_table;

import java.util.List;

public interface Family_tableService {
    int insertFamily_table(Family_table family_table);
    int deleteFamily_table(Integer id);
    int updateFamily_table(Family_table family_table);
    Family_table findFamily_table(Integer id);
    List<Family_table> findAll();
}
