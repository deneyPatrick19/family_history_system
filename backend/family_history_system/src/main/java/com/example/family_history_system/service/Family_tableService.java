package com.example.family_history_system.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.entity.Family_table;

import java.util.List;

public interface Family_tableService extends IService<Family_table> {
    List<Family_table> findAll();
    List<Family_table> findByUserId(Integer userId);
    Response deleteFamilyTableAndAllData(Integer familyTableId);
}
