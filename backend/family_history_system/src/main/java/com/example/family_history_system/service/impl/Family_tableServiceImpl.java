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

    public int insert(Family_table family_table){
        return family_tableMapper.insert(family_table);
    }
    public int delete(Integer id){
        return family_tableMapper.deleteById(id);
    }
    public int update(Family_table family_table){
        return family_tableMapper.updateById(family_table);
    }
    public Family_table findById(Integer id){
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
        eventMapper.deleteByFamilyTableId(familyTableId);
        relationMapper.deleteByFamilyTableId(familyTableId);
        memberMapper.deleteByFamilyTableId(familyTableId);
        family_tableMapper.deleteById(familyTableId);
    }
}
