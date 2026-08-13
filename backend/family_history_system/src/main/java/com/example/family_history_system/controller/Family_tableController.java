package com.example.family_history_system.controller;

import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.entity.Family_table;
import com.example.family_history_system.service.Family_tableService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/family-table")
@CrossOrigin
public class Family_tableController {

    @Autowired
    private Family_tableService familyTableService;

    @PostMapping("/insert")
    public Response insert(@RequestBody Family_table familyTable){
        boolean res = familyTableService.save(familyTable);
        return res ? Response.buildSuccess("添加家族表成功") : Response.buildFault("添加家族表失败");
    }

    @PostMapping("/update")
    public Response update(@RequestBody Family_table familyTable){
        boolean res = familyTableService.updateById(familyTable);
        return res ? Response.buildSuccess("更新家族表成功") : Response.buildFault("更新家族表失败");
    }

    @PostMapping("/delete")
    public Response delete(@RequestBody Family_table familyTable){
        boolean res = familyTableService.removeById(familyTable.getId());
        return res ? Response.buildSuccess("删除家族表成功") : Response.buildFault("删除家族表失败");
    }

    @PostMapping("/find")
    public Response find(@RequestBody Family_table familyTable){
        Family_table result = familyTableService.getById(familyTable.getId());
        return result != null ? Response.buildSuccess("获取家族表成功", result) : Response.buildFault("家族表不存在");
    }

    @GetMapping("/findall")
    public Response findAll(){
        return Response.buildSuccess("获取所有家族表成功", familyTableService.findAll());
    }

    @GetMapping("/user/{userId}")
    public Response getUserFamilyTables(@PathVariable Integer userId) {
        try {
            List<Family_table> familyTables = familyTableService.findByUserId(userId);
            return Response.buildSuccess("获取用户家族表成功", familyTables);
        } catch (Exception e) {
            return Response.buildFault("获取用户家族表失败: " + e.getMessage());
        }
    }

    @PostMapping("/create")
    public Response createFamilyTable(@RequestBody Map<String, Object> tableData) {
        try {
            Family_table familyTable = new Family_table();
            familyTable.setUser_id(((Number) tableData.get("userId")).intValue());
            familyTable.setTable_name((String) tableData.get("tableName"));
            familyTable.setContent((String) tableData.get("content"));
            familyTable.setEstablish_time(new java.sql.Date(System.currentTimeMillis()));

            familyTableService.save(familyTable);
            Integer tableId = familyTable.getId(); // 获取插入后的ID

            return Response.buildSuccess("创建家族表成功").withExtra("tableId", tableId);
        } catch (Exception e) {
            return Response.buildFault("创建家族表失败: " + e.getMessage());
        }
    }

    @PostMapping("/update-family-table")
    public Response updateFamilyTable(@RequestBody Map<String, Object> tableData) {
        try {
            Family_table familyTable = new Family_table();
            familyTable.setId(((Number) tableData.get("id")).intValue());
            familyTable.setTable_name((String) tableData.get("tableName"));
            familyTable.setContent((String) tableData.get("content"));
            boolean updateRes = familyTableService.updateById(familyTable);
            return updateRes
                    ? Response.buildSuccess("编辑家族表成功")
                    : Response.buildFault("编辑家族表失败");
        } catch (Exception e) {
            return Response.buildFault("编辑家族表失败: " + e.getMessage());
        }
    }

    @PostMapping("/delete-family-table")
    public Response deleteFamilyTable(@RequestBody Map<String, Object> tableData) {
        try {
            Integer id = ((Number) tableData.get("id")).intValue();
            return familyTableService.deleteFamilyTableAndAllData(id);
        } catch (Exception e) {
            return Response.buildFault("删除家族表失败: " + e.getMessage());
        }
    }
}
