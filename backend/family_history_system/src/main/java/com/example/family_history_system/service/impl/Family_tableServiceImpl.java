package com.example.family_history_system.service.impl;

import com.example.family_history_system.entity.Family_table;
import com.example.family_history_system.mapper.Family_tableMapper;
import com.example.family_history_system.mapper.MemberMapper;
import com.example.family_history_system.mapper.RelationMapper;
import com.example.family_history_system.mapper.EventMapper;
import com.example.family_history_system.service.Family_tableService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class Family_tableServiceImpl implements Family_tableService {

    @Autowired
    private Family_tableMapper family_tableMapper;
    @Autowired
    private MemberMapper memberMapper;
    @Autowired
    private RelationMapper relationMapper;
    @Autowired
    private EventMapper eventMapper;

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
    public List<Family_table> findByUserId(Integer userId){
        return family_tableMapper.selectByUserId(userId);
    }

    @Override
    public void deleteFamilyTableAndAllData(Integer familyTableId) {
        // 1. 删除事件（先删事件，防止外键约束）
        eventMapper.deleteByFamilyTableId(familyTableId);
        // 2. 删除关系
        relationMapper.deleteByFamilyTableId(familyTableId);
        // 3. 删除成员
        memberMapper.deleteByFamilyTableId(familyTableId);
        // 4. 删除家谱表
        family_tableMapper.deleteById(familyTableId);
    }
}
