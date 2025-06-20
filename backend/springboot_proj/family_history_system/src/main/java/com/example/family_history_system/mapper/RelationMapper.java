package com.example.family_history_system.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Relationship;
import io.swagger.models.auth.In;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.type.JdbcType;

import java.util.List;

@Mapper
public interface RelationMapper extends BaseMapper<Relationship> {
    @Select("select * from `system`.relationship")
    @Results({
            @Result(property = "member_id1", column = "member_id1", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id2", column = "member_id2", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "relation", column = "relation", jdbcType = JdbcType.VARCHAR)
    })
    List<Relationship> findAllRelation();

    @Select("select * from `system`.relationship where relationship.member_id1=#{id1} and relationship.member_id2=#{id2}")
    @Results({
            @Result(property = "member_id1", column = "member_id1", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id2", column = "member_id2", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "relation", column = "relation", jdbcType = JdbcType.VARCHAR)
    })
    Relationship findRelationById(@Param("id1") Integer id1,@Param("id2") Integer id2);

    @Delete("delete from `system`.relationship where relationship.member_id1=#{id1} and relationship.member_id2=#{id2}")
    @Results({
            @Result(property = "member_id1", column = "member_id1", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id2", column = "member_id2", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "relation", column = "relation", jdbcType = JdbcType.VARCHAR)
    })
    int deleteRelationById(@Param("id1") Integer id1,@Param("id2") Integer id2);

    @Update("update `system`.relationship set relationship.relation=#{relation} where member_id1=#{member_id1} and member_id2=#{member_id2}")
    @Results({
            @Result(property = "member_id1", column = "member_id1", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id2", column = "member_id2", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "relation", column = "relation", jdbcType = JdbcType.VARCHAR)
    })
    int updateRelationById(Relationship relation);
}
