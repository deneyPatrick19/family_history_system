package com.example.family_history_system.service;

import com.example.family_history_system.entity.Family_table;

import java.util.List;

public interface Family_tableService {
    int insert(Family_table family_table);
    int delete(Integer id);
    int update(Family_table family_table);
    Family_table findById(Integer id);
    List<Family_table> findAll();
    List<Family_table> findByUserId(Integer userId);
    void deleteFamilyTableAndAllData(Integer familyTableId);
}
