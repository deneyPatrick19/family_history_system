package com.example.family_history_system.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Event;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface EventMapper extends BaseMapper<Event> {
    /**
     * 删除家族表下所有成员的全部事件
     * @param familyTableId 家族表ID
     * @return 受影响行数
     */
    int deleteByFamilyTableId(@Param("familyTableId") Integer familyTableId);
}
