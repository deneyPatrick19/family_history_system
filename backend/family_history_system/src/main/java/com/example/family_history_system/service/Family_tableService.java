package com.example.family_history_system.service;

import com.example.family_history_system.entity.Family_table;

import java.util.List;

public interface Family_tableService {
    int insertFamily_table(Family_table family_table);
    int deleteFamily_table(Integer id);
    int updateFamily_table(Family_table family_table);
    Family_table findFamily_table(Integer id);
    List<Family_table> findAll();
    List<Family_table> findByUserId(Integer userId);
    
    // 为了兼容性，添加别名方法
    default int insert(Family_table family_table) {
        return insertFamily_table(family_table);
    }
    
    default int delete(Integer id) {
        return deleteFamily_table(id);
    }
    
    default int update(Family_table family_table) {
        return updateFamily_table(family_table);
    }
    
    default Family_table findById(Integer id) {
        return findFamily_table(id);
    }

    /**
     * 级联删除家谱表及其所有成员、关系、事件等
     */
    void deleteFamilyTableAndAllData(Integer familyTableId);
}
