package com.example.family_history_system.service.impl;
import com.example.family_history_system.entity.Event;
import com.example.family_history_system.mapper.EventMapper;
import com.example.family_history_system.service.EventService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class EventServiceImpl implements EventService {

    @Autowired
    private EventMapper eventMapper;

    public int insertEvent(Event event){
        return eventMapper.insert(event);
    }
    public int deleteById(Integer id){
        return eventMapper.deleteById(id);
    }
    public int updateById(Event event){
        return eventMapper.updateById(event);
    }
    public Event findById(Integer id){
        return eventMapper.selectById(id);
    }
    public List<Event> findAll(){
        return eventMapper.findAllEvent();
    }

}
