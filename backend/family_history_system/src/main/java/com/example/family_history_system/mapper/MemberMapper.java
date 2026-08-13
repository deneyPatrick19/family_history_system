package com.example.family_history_system.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Member;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface MemberMapper extends BaseMapper<Member> {
    /**
     * 按家族表ID删除其下全部成员
     * @param familyTableId 家族表ID
     * @return 受影响行数
     */
    int deleteByFamilyTableId(@Param("familyTableId") Integer familyTableId);
}
