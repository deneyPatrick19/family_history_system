package com.example.family_history_system.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.family_history_system.entity.Relationship;

import java.util.List;

public interface RelationService extends IService<Relationship> {
    Boolean insertRelation(Relationship relation);
    List<Relationship> findAllRelation();
    Relationship findRelationById(Integer id1, Integer id2);
    Boolean deleteRelationById(Integer id1, Integer id2);
    Boolean updateRelationById(Relationship relation);
    int deleteRelationsByMemberId(Integer memberId);
    List<Relationship> findByMemberId2(Integer memberId2);
}
