package com.example.family_history_system.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.entity.Family_table;
import com.example.family_history_system.mapper.EventMapper;
import com.example.family_history_system.mapper.Family_tableMapper;
import com.example.family_history_system.mapper.MemberMapper;
import com.example.family_history_system.mapper.RelationMapper;
import com.example.family_history_system.service.Family_tableService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class Family_tableServiceImpl extends ServiceImpl<Family_tableMapper, Family_table> implements Family_tableService {

    @Autowired
    private MemberMapper memberMapper;
    @Autowired
    private RelationMapper relationMapper;
    @Autowired
    private EventMapper eventMapper;

    /**
     * 查询全部家族表
     * @return 家族表列表
     */
    @Override
    public List<Family_table> findAll(){
        return this.list(new LambdaQueryWrapper<>());
    }

    /**
     * 按用户ID查询其名下家族表
     * @param userId 用户ID
     * @return 家族表列表
     */
    @Override
    public List<Family_table> findByUserId(Integer userId){
        return this.list(new LambdaQueryWrapper<Family_table>().eq(Family_table::getUser_id, userId));
    }

    /**
     * 级联删除家族表及其全部成员、关系、事件
     * @param familyTableId 家族表ID
     */
    @Override
    public Response deleteFamilyTableAndAllData(Integer familyTableId) {
        int res1 = eventMapper.deleteByFamilyTableId(familyTableId);
        int res2 = relationMapper.deleteByFamilyTableId(familyTableId);
        int res3 =  memberMapper.deleteByFamilyTableId(familyTableId);
        boolean res4 = this.removeById(familyTableId);
        if (res1 > 0 || res2 > 0 || res3 > 0 || res4) {
            return Response.buildSuccess("删除家族表及其所有数据成功");
        }
        return Response.buildFault("删除家族表及其所有数据失败");
    }
}
