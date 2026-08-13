package com.example.family_history_system.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Relationship;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface RelationMapper extends BaseMapper<Relationship> {
    /**
     * 删除家族表下所有成员涉及的全部关系（含 member_id1 或 member_id2 任一匹配）
     * @param familyTableId 家族表ID
     * @return 受影响行数
     */
    int deleteByFamilyTableId(@Param("familyTableId") Integer familyTableId);
}
