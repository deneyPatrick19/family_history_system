package com.example.family_history_system.controller;
import com.example.family_history_system.entity.Event;
import com.example.family_history_system.service.EventService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@CrossOrigin
@RestController
@RequestMapping("/event")
public class EventController {

    @Autowired
    private EventService eventService;

    @PostMapping("/insert")
    public int insertEvent(@RequestBody Event event) {
        return eventService.insertEvent(event);
    }
    @PostMapping("/delete")
    public int deleteEventById(@RequestParam Integer id){
        return eventService.deleteById(id);
    }
    @PostMapping("/update")
    public int updateEventById(@RequestBody Event event){
        return eventService.updateById(event);
    }
    @PostMapping("/find")
    public Event findById(@RequestParam Integer id){
        return eventService.findById(id);
    }
    @GetMapping("/findall")
    public List<Event> findAllEvent(){
        return eventService.findAll();
    }
}
