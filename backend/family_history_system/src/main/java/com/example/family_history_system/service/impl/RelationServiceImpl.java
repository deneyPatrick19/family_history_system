package com.example.family_history_system.service.impl;

import com.example.family_history_system.entity.Relationship;
import com.example.family_history_system.mapper.RelationMapper;
import com.example.family_history_system.service.RelationService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class RelationServiceImpl implements RelationService {
    @Autowired
    private RelationMapper relationMapper;

    public int insertRelation(Relationship relation){
        return relationMapper.insert(relation);
    }
    public List<Relationship> findAllRelation(){
        return relationMapper.findAllRelation();
    }
    public Relationship findRelationById(Integer id1,Integer id2){
        return relationMapper.findRelationById(id1,id2);
    }
    public int deleteRelationById(Integer id1,Integer id2){
        return relationMapper.deleteRelationById(id1,id2);
    }
    public int updateRelationById(Relationship relation){
        return relationMapper.updateRelationById(relation);
    }
    public int deleteRelationsByMemberId(Integer memberId){
        return relationMapper.deleteRelationsByMemberId(memberId);
    }

    @Override
    public List<Relationship> findByMemberId2(Integer memberId2) {
        return relationMapper.findByMemberId2(memberId2);
    }
}
