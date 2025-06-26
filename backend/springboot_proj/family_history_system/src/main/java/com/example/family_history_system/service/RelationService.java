package com.example.family_history_system.service;

import com.example.family_history_system.entity.Relationship;
import java.util.List;

public interface RelationService {
    int insertRelation(Relationship relation);
    List<Relationship> findAllRelation();
    Relationship findRelationById(Integer id1, Integer id2);
    int deleteRelationById(Integer id1, Integer id2);
    int updateRelationById(Relationship relation);
    int deleteRelationsByMemberId(Integer memberId);
    boolean existsSiblingRelation(int memberId1, int memberId2);
}
