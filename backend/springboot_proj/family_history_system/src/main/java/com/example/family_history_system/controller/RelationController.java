package com.example.family_history_system.controller;
import com.example.family_history_system.entity.Relationship;
import com.example.family_history_system.service.RelationService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@RestController
@RequestMapping("/relation")
public class RelationController {
    @Autowired
    RelationService relationService;

    @PostMapping("/add")
    public int insert(@RequestBody Relationship relation){
        return relationService.insertRelation(relation);
    }
    @PostMapping("/find")
    public Relationship findById(@Param("id1") Integer id1, @Param("id2") Integer id2){
        return relationService.findRelationById(id1,id2);
    }
    @GetMapping("/findall")
    public List<Relationship> findAll(){
        return relationService.findAllRelation();
    }
    @PostMapping("/delete")
    public int deleteRelationById(@Param("id1") Integer id1, @Param("id2") Integer id2){
        return relationService.deleteRelationById(id1,id2);
    }
    @PostMapping("/update")
    public int updateRelationById(@RequestBody Relationship relation){
        return relationService.updateRelationById(relation);
    }

}
