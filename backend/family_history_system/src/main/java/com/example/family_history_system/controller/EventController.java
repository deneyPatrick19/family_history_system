package com.example.family_history_system.controller;
import com.example.family_history_system.entity.Event;
import com.example.family_history_system.service.EventService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import java.util.List;
import java.util.Map;
import java.util.HashMap;

@CrossOrigin
@RestController
@RequestMapping("/event")
public class EventController {

    @Autowired
    private EventService eventService;

    /**
     * 获取指定成员的所有事件
     */
    @GetMapping("/member/{memberId}")
    public Map<String, Object> getMemberEvents(@PathVariable Integer memberId) {
        Map<String, Object> result = new HashMap<>();
        try {
            List<Event> events = eventService.findByMemberId(memberId);
            result.put("success", true);
            result.put("data", events);
            result.put("message", "获取成员事件成功");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取成员事件失败: " + e.getMessage());
        }
        return result;
    }

    @PostMapping("/insert")
    public Map<String, Object> insertEvent(@RequestBody Event event) {
        Map<String, Object> result = new HashMap<>();
        try {
            int res = eventService.insertEvent(event);
            result.put("success", res > 0);
            result.put("message", res > 0 ? "添加事件成功" : "添加事件失败");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "添加事件失败: " + e.getMessage());
        }
        return result;
    }

    @PostMapping("/delete")
    public Map<String, Object> deleteEventById(@RequestParam Integer id) {
        Map<String, Object> result = new HashMap<>();
        try {
            int res = eventService.deleteById(id);
            result.put("success", res > 0);
            result.put("message", res > 0 ? "删除事件成功" : "删除事件失败");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "删除事件失败: " + e.getMessage());
        }
        return result;
    }

    @PostMapping("/update")
    public Map<String, Object> updateEventById(@RequestBody Event event) {
        Map<String, Object> result = new HashMap<>();
        try {
            int res = eventService.updateById(event);
            result.put("success", res > 0);
            result.put("message", res > 0 ? "更新事件成功" : "更新事件失败");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "更新事件失败: " + e.getMessage());
        }
        return result;
    }

    @PostMapping("/find")
    public Map<String, Object> findById(@RequestParam Integer id) {
        Map<String, Object> result = new HashMap<>();
        try {
            Event event = eventService.findById(id);
            result.put("success", event != null);
            result.put("data", event);
            result.put("message", event != null ? "获取事件成功" : "事件不存在");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取事件失败: " + e.getMessage());
        }
        return result;
    }

    @GetMapping("/findall")
    public Map<String, Object> findAllEvent() {
        Map<String, Object> result = new HashMap<>();
        try {
            List<Event> events = eventService.findAll();
            result.put("success", true);
            result.put("data", events);
            result.put("message", "获取所有事件成功");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取所有事件失败: " + e.getMessage());
        }
        return result;
    }
}
