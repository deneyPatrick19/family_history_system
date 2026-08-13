package com.example.family_history_system.service;
import com.baomidou.mybatisplus.extension.service.IService;
import com.example.family_history_system.entity.Event;
import java.util.List;

public interface EventService extends IService<Event> {
    List<Event> findAll();
    List<Event> findByMemberId(Integer memberId);
    int deleteByMemberId(Integer memberId);
}
