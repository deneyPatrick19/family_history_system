package com.example.family_history_system.service.impl;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.family_history_system.entity.Event;
import com.example.family_history_system.mapper.EventMapper;
import com.example.family_history_system.service.EventService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class EventServiceImpl extends ServiceImpl<EventMapper, Event> implements EventService {

    /**
     * 查询全部事件
     * @return 事件列表
     */
    @Override
    public List<Event> findAll(){
        return this.list(new LambdaQueryWrapper<>());
    }

    /**
     * 按成员ID查询其全部事件
     * @param memberId 成员ID
     * @return 事件列表
     */
    @Override
    public List<Event> findByMemberId(Integer memberId){
        return this.list(new LambdaQueryWrapper<Event>().eq(Event::getMember_id, memberId));
    }

    /**
     * 删除指定成员的全部事件
     * @param memberId 成员ID
     * @return 受影响行数
     */
    @Override
    public int deleteByMemberId(Integer memberId){
        return this.baseMapper.delete(new LambdaQueryWrapper<Event>().eq(Event::getMember_id, memberId));
    }
}
