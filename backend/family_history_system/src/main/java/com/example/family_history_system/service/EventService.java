package com.example.family_history_system.service;
import com.example.family_history_system.entity.Event;
import java.util.List;

public interface EventService {
    int insertEvent(Event event);
    int deleteById(Integer id);
    int updateById(Event event);
    Event findById(Integer id);
    List<Event> findAll();
    List<Event> findByMemberId(Integer memberId);
}
