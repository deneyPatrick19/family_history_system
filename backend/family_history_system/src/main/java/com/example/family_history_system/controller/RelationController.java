package com.example.family_history_system.controller;
import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.entity.Relationship;
import com.example.family_history_system.service.RelationService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@CrossOrigin
@RestController
@RequestMapping("/relation")
public class RelationController {
    @Autowired
    RelationService relationService;

    @PostMapping("/add")
    public Response insert(@RequestBody Relationship relation){
        boolean res = relationService.insertRelation(relation);
        return res ? Response.buildSuccess("添加关系成功") : Response.buildFault("添加关系失败");
    }
    @PostMapping("/find")
    public Response findById(@Param("id1") Integer id1, @Param("id2") Integer id2){
        Relationship result = relationService.findRelationById(id1, id2);
        return result != null ? Response.buildSuccess("获取关系成功", result) : Response.buildFault("关系不存在");
    }
    @GetMapping("/findall")
    public Response findAll(){
        return Response.buildSuccess("获取所有关系成功", relationService.findAllRelation());
    }
    @PostMapping("/delete")
    public Response deleteRelationById(@Param("id1") Integer id1, @Param("id2") Integer id2){
        boolean res = relationService.deleteRelationById(id1, id2);
        return res ? Response.buildSuccess("删除关系成功") : Response.buildFault("删除关系失败");
    }
    @PostMapping("/update")
    public Response updateRelationById(@RequestBody Relationship relation){
        boolean res = relationService.updateRelationById(relation);
        return res ? Response.buildSuccess("更新关系成功") : Response.buildFault("更新关系失败");
    }

}
