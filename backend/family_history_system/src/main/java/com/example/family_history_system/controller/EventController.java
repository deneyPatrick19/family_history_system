package com.example.family_history_system.controller;
import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.entity.Event;
import com.example.family_history_system.service.EventService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@CrossOrigin
@RestController
@RequestMapping("/event")
public class EventController {

    @Autowired
    private EventService eventService;

    @GetMapping("/member/{memberId}")
    public Response getMemberEvents(@PathVariable Integer memberId) {
        try {
            return Response.buildSuccess("获取成员事件成功", eventService.findByMemberId(memberId));
        } catch (Exception e) {
            return Response.buildFault("获取成员事件失败: " + e.getMessage());
        }
    }

    @PostMapping("/insert")
    public Response insertEvent(@RequestBody Event event) {
        try {
            boolean res = eventService.save(event);
            return res ? Response.buildSuccess("添加事件成功") : Response.buildFault("添加事件失败");
        } catch (Exception e) {
            return Response.buildFault("添加事件失败: " + e.getMessage());
        }
    }

    @PostMapping("/delete")
    public Response deleteEventById(@RequestParam Integer id) {
        try {
            boolean res = eventService.removeById(id);
            return res ? Response.buildSuccess("删除事件成功") : Response.buildFault("删除事件失败");
        } catch (Exception e) {
            return Response.buildFault("删除事件失败: " + e.getMessage());
        }
    }

    @PostMapping("/update")
    public Response updateEventById(@RequestBody Event event) {
        try {
            boolean res = eventService.updateById(event);
            return res ? Response.buildSuccess("更新事件成功") : Response.buildFault("更新事件失败");
        } catch (Exception e) {
            return Response.buildFault("更新事件失败: " + e.getMessage());
        }
    }

    @PostMapping("/find")
    public Response findById(@RequestParam Integer id) {
        try {
            Event event = eventService.getById(id);
            return event != null
                    ? Response.buildSuccess("获取事件成功", event)
                    : Response.buildFault("事件不存在");
        } catch (Exception e) {
            return Response.buildFault("获取事件失败: " + e.getMessage());
        }
    }

    @GetMapping("/findall")
    public Response findAllEvent() {
        try {
            return Response.buildSuccess("获取所有事件成功", eventService.findAll());
        } catch (Exception e) {
            return Response.buildFault("获取所有事件失败: " + e.getMessage());
        }
    }
}
