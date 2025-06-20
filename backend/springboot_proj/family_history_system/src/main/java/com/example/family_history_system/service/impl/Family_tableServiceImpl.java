package com.example.family_history_system.service.impl;

import com.example.family_history_system.entity.Family_table;
import com.example.family_history_system.mapper.Family_tableMapper;
import com.example.family_history_system.service.Family_tableService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class Family_tableServiceImpl implements Family_tableService {

    @Autowired
    private Family_tableMapper family_tableMapper;

    public int insertFamily_table(Family_table family_table){
        return family_tableMapper.insert(family_table);
    }
    public int deleteFamily_table(Integer id){
        return family_tableMapper.deleteById(id);
    }
    public int updateFamily_table(Family_table family_table){
        return family_tableMapper.updateById(family_table);
    }
    public Family_table findFamily_table(Integer id){
        return family_tableMapper.selectById(id);
    }
    public List<Family_table> findAll(){
        return family_tableMapper.FindAllFamilyTable();
    }
}
