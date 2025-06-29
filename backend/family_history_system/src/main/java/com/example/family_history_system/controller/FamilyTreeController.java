package com.example.family_history_system.controller;

import com.example.family_history_system.entity.Member;
import com.example.family_history_system.entity.Relationship;
import com.example.family_history_system.service.MemberService;
import com.example.family_history_system.service.RelationService;
import com.example.family_history_system.service.EventService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.text.SimpleDateFormat;
import java.util.*;

@RestController
@RequestMapping("/family-tree")
@CrossOrigin
public class FamilyTreeController {

    @Autowired
    private MemberService memberService;
    @Autowired
    private RelationService relationService;
    @Autowired
    private EventService eventService;

    @GetMapping("/{familyTableId}")
    public Map<String, Object> getFamilyTree(@PathVariable Integer familyTableId) {
        Map<String, Object> result = new HashMap<>();
        try {
            List<Member> members = memberService.findByFamilyTableId(familyTableId);
            List<Relationship> relationships = relationService.findAllRelation();

            List<Map<String, Object>> treeData = buildFamilyTree(members, relationships);
            
            result.put("success", true);
            result.put("data", treeData);
            result.put("message", "获取家谱树成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取家谱树失败: " + e.getMessage());
        }
        return result;
    }

    @PostMapping("/save-node")
    public Map<String, Object> saveNode(@RequestBody Map<String, Object> nodeData) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            Member member = new Member();

            Object familyTableIdObj = nodeData.get("familyTableId");
            if (familyTableIdObj instanceof Number) {
                member.setFamily_table_id(((Number) familyTableIdObj).intValue());
            } else if (familyTableIdObj instanceof String) {
                member.setFamily_table_id(Integer.parseInt((String) familyTableIdObj));
            } else {
                throw new IllegalArgumentException("familyTableId must be a number");
            }
            
            member.setName((String) nodeData.get("name"));
            member.setGender((String) nodeData.get("gender"));
            member.setBio((String) nodeData.get("bio"));

            if (nodeData.get("birthDate") != null && !((String) nodeData.get("birthDate")).isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                Date birthDate = sdf.parse((String) nodeData.get("birthDate"));
                member.setBirthdate(new java.sql.Date(birthDate.getTime()));
            }

            if (nodeData.get("deathDate") != null && !((String) nodeData.get("deathDate")).isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                Date deathDate = sdf.parse((String) nodeData.get("deathDate"));
                member.setDeathdate(new java.sql.Date(deathDate.getTime()));
            }
            
            memberService.insertMember(member);
            Integer memberId = member.getId(); // 获取插入后的ID

            if (nodeData.get("parentId") != null) {
                Relationship relation = new Relationship();

                Object parentIdObj = nodeData.get("parentId");
                if (parentIdObj instanceof Number) {
                    relation.setMember_id1(((Number) parentIdObj).intValue());
                } else if (parentIdObj instanceof String) {
                    relation.setMember_id1(Integer.parseInt((String) parentIdObj));
                } else {
                    throw new IllegalArgumentException("parentId must be a number");
                }
                
                relation.setMember_id2(memberId);
                relation.setRelation((String) nodeData.get("relationship"));
                relationService.insertRelation(relation);
            }

            if (nodeData.get("childId") != null) {
                Relationship relation = new Relationship();
                relation.setMember_id1(memberId);

                Object childIdObj = nodeData.get("childId");
                if (childIdObj instanceof Number) {
                    relation.setMember_id2(((Number) childIdObj).intValue());
                } else if (childIdObj instanceof String) {
                    relation.setMember_id2(Integer.parseInt((String) childIdObj));
                } else {
                    throw new IllegalArgumentException("childId must be a number");
                }
                
                relation.setRelation((String) nodeData.get("relationship"));
                relationService.insertRelation(relation);
            }
            
            result.put("success", true);
            result.put("memberId", memberId);
            result.put("message", "保存节点成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "保存节点失败: " + e.getMessage());
        }
        
        return result;
    }

    @PostMapping("/update-node")
    public Map<String, Object> updateNode(@RequestBody Map<String, Object> nodeData) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            Member member = new Member();
            

            Object idObj = nodeData.get("id");
            if (idObj instanceof Number) {
                member.setId(((Number) idObj).intValue());
            } else if (idObj instanceof String) {
                member.setId(Integer.parseInt((String) idObj));
            } else {
                throw new IllegalArgumentException("id must be a number");
            }
            
            member.setName((String) nodeData.get("name"));
            member.setGender((String) nodeData.get("gender"));
            member.setBio((String) nodeData.get("bio"));

            if (nodeData.get("birthDate") != null && !((String) nodeData.get("birthDate")).isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                Date birthDate = sdf.parse((String) nodeData.get("birthDate"));
                member.setBirthdate(new java.sql.Date(birthDate.getTime()));
            }

            if (nodeData.get("deathDate") != null && !((String) nodeData.get("deathDate")).isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                Date deathDate = sdf.parse((String) nodeData.get("deathDate"));
                member.setDeathdate(new java.sql.Date(deathDate.getTime()));
            }
            
            memberService.updateMember(member);

            if (nodeData.get("relationship") != null) {
                String newRelationship = (String) nodeData.get("relationship");
                Integer memberId = member.getId();

                List<Relationship> parentRelations = relationService.findByMemberId2(memberId);
                for (Relationship relation : parentRelations) {
                    if (relation.getRelation().equals("父亲") || relation.getRelation().equals("母亲") || 
                        relation.getRelation().equals("儿子") || relation.getRelation().equals("女儿")) {

                        relation.setRelation(newRelationship);
                        relationService.updateRelationById(relation);
                        break;
                    }
                }
            }
            
            result.put("success", true);
            result.put("message", "更新节点成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "更新节点失败: " + e.getMessage());
        }
        
        return result;
    }

    @GetMapping("/check-parent/{memberId}")
    public Map<String, Object> checkParent(@PathVariable Integer memberId) {
        Map<String, Object> result = new HashMap<>();
        
        try {

            List<Relationship> parentRelations = relationService.findByMemberId2(memberId);
            boolean hasParent = false;
            String parentName = null;
            
            for (Relationship relation : parentRelations) {

                if (relation.getRelation().equals("父亲") || relation.getRelation().equals("母亲")) {
                    hasParent = true;
                    Member parent = memberService.findById(relation.getMember_id1());
                    if (parent != null) {
                        parentName = parent.getName();
                    }
                    break;
                }
            }
            
            result.put("success", true);
            result.put("hasParent", hasParent);
            result.put("parentName", parentName);
            result.put("message", hasParent ? "该节点已有父节点" : "该节点没有父节点");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "检查父节点失败: " + e.getMessage());
        }
        
        return result;
    }

    @PostMapping("/delete-node")
    public Map<String, Object> deleteNode(@RequestBody Map<String, Object> nodeData) {
        Map<String, Object> result = new HashMap<>();
        
        try {

            Object idObj = nodeData.get("id");
            Integer memberId;
            if (idObj instanceof Number) {
                memberId = ((Number) idObj).intValue();
            } else if (idObj instanceof String) {
                memberId = Integer.parseInt((String) idObj);
            } else {
                throw new IllegalArgumentException("id must be a number");
            }
            
            // 删除相关的事件
            eventService.deleteByMemberId(memberId);
            // 删除相关的关系
            relationService.deleteRelationsByMemberId(memberId);
            // 删除成员
            memberService.deleteMember(memberId);
            
            result.put("success", true);
            result.put("message", "删除节点成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "删除节点失败: " + e.getMessage());
        }
        
        return result;
    }

    private List<Map<String, Object>> buildFamilyTree(List<Member> members, List<Relationship> relationships) {
        Map<Integer, Map<String, Object>> memberMap = new HashMap<>();
        Map<Integer, List<Integer>> childrenMap = new HashMap<>();
        Map<Integer, Integer> parentMap = new HashMap<>();
        Map<Integer, String> relationshipMap = new HashMap<>(); // 存储关系信息

        for (Member member : members) {
            Map<String, Object> node = new HashMap<>();
            node.put("id", member.getId());
            node.put("name", member.getName());
            node.put("gender", member.getGender());
            node.put("birthDate", member.getBirthdate());
            node.put("deathDate", member.getDeathdate());
            node.put("bio", member.getBio());
            node.put("children", new ArrayList<>());
            
            memberMap.put(member.getId(), node);
            childrenMap.put(member.getId(), new ArrayList<>());
        }

        for (Relationship relation : relationships) {
            String relationType = relation.getRelation();

            if (relationType.equals("父亲") || relationType.equals("母亲") || 
                relationType.equals("儿子") || relationType.equals("女儿")) {

                List<Integer> children = childrenMap.get(relation.getMember_id1());
                if (children != null) {
                    children.add(relation.getMember_id2());
                }
                parentMap.put(relation.getMember_id2(), relation.getMember_id1());
                // 存储关系信息
                relationshipMap.put(relation.getMember_id2(), relationType);
            }
        }
        

        for (Map.Entry<Integer, Integer> entry : parentMap.entrySet()) {
            Integer childId = entry.getKey();
            Integer parentId = entry.getValue();
            
            Map<String, Object> childNode = memberMap.get(childId);
            Map<String, Object> parentNode = memberMap.get(parentId);
            
            if (childNode != null && parentNode != null) {
                childNode.put("parentId", parentId);
                childNode.put("parentName", parentNode.get("name"));
                // 添加关系信息
                String relationship = relationshipMap.get(childId);
                if (relationship != null) {
                    childNode.put("relationship", relationship);
                }
            }
        }
        
        // 构建树结构
        List<Map<String, Object>> rootNodes = new ArrayList<>();
        Set<Integer> hasParent = new HashSet<>();
        
        for (Relationship relation : relationships) {

            if (relation.getRelation().equals("父亲") || relation.getRelation().equals("母亲") || 
                relation.getRelation().equals("儿子") || relation.getRelation().equals("女儿")) {
                hasParent.add(relation.getMember_id2());
            }
        }
        
        for (Member member : members) {
            if (!hasParent.contains(member.getId())) {

                Map<String, Object> rootNode = memberMap.get(member.getId());
                buildChildren(rootNode, childrenMap, parentMap, memberMap);
                rootNodes.add(rootNode);
            }
        }
        
        return rootNodes;
    }

    private void buildChildren(Map<String, Object> parentNode, Map<Integer, List<Integer>> childrenMap, 
                              Map<Integer, Integer> parentMap, Map<Integer, Map<String, Object>> memberMap) {
        Integer parentId = (Integer) parentNode.get("id");
        List<Integer> childrenIds = childrenMap.get(parentId);
        
        List<Map<String, Object>> children = new ArrayList<>();
        
        if (childrenIds != null && !childrenIds.isEmpty()) {

            childrenIds.sort((id1, id2) -> {
                Map<String, Object> node1 = memberMap.get(id1);
                Map<String, Object> node2 = memberMap.get(id2);
                Date date1 = (Date) node1.get("birthDate");
                Date date2 = (Date) node2.get("birthDate");
                
                if (date1 == null && date2 == null) return 0;
                if (date1 == null) return 1;
                if (date2 == null) return -1;
                
                return date1.compareTo(date2);
            });
            
            for (Integer childId : childrenIds) {
                Map<String, Object> childNode = memberMap.get(childId);
                if (childNode != null) {
                    // 递归构建子节点
                    buildChildren(childNode, childrenMap, parentMap, memberMap);
                    children.add(childNode);
                }
            }
        }

        parentNode.put("children", children);
    }

    @GetMapping("/members/{familyTableId}")
    public Map<String, Object> getAllMembers(@PathVariable Integer familyTableId) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            List<Member> members = memberService.findByFamilyTableId(familyTableId);

            List<Relationship> relationships = relationService.findAllRelation();

            List<Map<String, Object>> memberList = new ArrayList<>();
            
            for (Member member : members) {
                Map<String, Object> memberInfo = new HashMap<>();
                memberInfo.put("id", member.getId());
                memberInfo.put("name", member.getName());
                memberInfo.put("gender", member.getGender());
                memberInfo.put("birthDate", member.getBirthdate());
                memberInfo.put("deathDate", member.getDeathdate());
                memberInfo.put("bio", member.getBio());
                
                // 查找父节点信息和关系信息
                String parentName = null;
                String relationship = null;
                for (Relationship relation : relationships) {
                    if (relation.getMember_id2().equals(member.getId()) && 
                        (relation.getRelation().equals("父亲") || relation.getRelation().equals("母亲") ||
                         relation.getRelation().equals("儿子") || relation.getRelation().equals("女儿"))) {
                        Member parent = memberService.findById(relation.getMember_id1());
                        if (parent != null) {
                            parentName = parent.getName();
                            relationship = relation.getRelation();
                        }
                        break;
                    }
                }
                
                memberInfo.put("parentName", parentName);
                memberInfo.put("relationship", relationship);
                
                memberList.add(memberInfo);
            }
            
            // 按姓名排序
            memberList.sort((a, b) -> {
                String nameA = (String) a.get("name");
                String nameB = (String) b.get("name");
                return nameA.compareTo(nameB);
            });
            
            result.put("success", true);
            result.put("data", memberList);
            result.put("message", "获取成员列表成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取成员列表失败: " + e.getMessage());
        }
        
        return result;
    }
} 