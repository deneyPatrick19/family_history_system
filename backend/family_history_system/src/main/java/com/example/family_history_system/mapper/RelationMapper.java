package com.example.family_history_system.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Relationship;
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
    
    @Delete("delete from `system`.relationship where member_id1=#{memberId} or member_id2=#{memberId}")
    int deleteRelationsByMemberId(@Param("memberId") Integer memberId);

    @Select("SELECT COUNT(*) FROM `system`.relationship WHERE relation = '兄弟' AND ((member_id1 = #{memberId1} AND member_id2 = #{memberId2}) OR (member_id1 = #{memberId2} AND member_id2 = #{memberId1}))")
    int existsSiblingRelation(@Param("memberId1") int memberId1, @Param("memberId2") int memberId2);

    @Select("select * from `system`.relationship where member_id2=#{memberId2}")
    @Results({
            @Result(property = "member_id1", column = "member_id1", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id2", column = "member_id2", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "relation", column = "relation", jdbcType = JdbcType.VARCHAR)
    })
    List<Relationship> findByMemberId2(@Param("memberId2") Integer memberId2);

    @Delete("delete from `system`.relationship where member_id1 in (select id from `system`.member where family_table_id = #{familyTableId}) or member_id2 in (select id from `system`.member where family_table_id = #{familyTableId})")
    int deleteByFamilyTableId(@Param("familyTableId") Integer familyTableId);
}
