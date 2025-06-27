<template>
  <div class="member-list">
    <div style="margin-bottom: 16px;">
      <el-select v-model="selectedFamilyTableId" placeholder="请选择家谱表" @change="onTableChange" style="width: 220px;">
        <el-option
          v-for="table in familyTables"
          :key="table.id"
          :label="table.name || table.tableName || table.table_name"
          :value="table.id"
        />
      </el-select>
    </div>
    <!-- 删除家族表选择器相关内容，直接显示成员列表界面 -->
    <div class="member-list-content">
      <div class="header">
        <h2>家族成员列表</h2>
        <div class="header-actions">
          <el-button type="primary" @click="refreshData" :loading="loading">
            <el-icon><Refresh /></el-icon>
            刷新
          </el-button>
        </div>
      </div>
      <div class="content">
        <div v-if="loading" class="loading">
          <el-skeleton :rows="10" animated />
        </div>
        
        <div v-else-if="members.length === 0" class="empty-state">
          <el-empty description="暂无成员信息" />
        </div>
        
        <div v-else class="member-table">
          <el-table 
            :data="members" 
            stripe 
            border 
            style="width: 100%"
            :header-cell-style="{ background: '#f5f7fa', color: '#606266' }"
          >
            <el-table-column prop="id" label="ID" width="80" align="center" />
            
            <el-table-column prop="name" label="姓名" width="120" align="center">
              <template #default="scope">
                <span class="member-name">{{ scope.row.name }}</span>
              </template>
            </el-table-column>
            
            <el-table-column prop="gender" label="性别" width="80" align="center">
              <template #default="scope">
                <el-tag :type="scope.row.gender === '男' ? 'primary' : 'danger'" size="small">
                  {{ scope.row.gender }}
                </el-tag>
              </template>
            </el-table-column>
            
            <el-table-column prop="birthDate" label="出生日期" width="120" align="center">
              <template #default="scope">
                <span v-if="scope.row.birthDate">{{ formatDate(scope.row.birthDate) }}</span>
                <span v-else class="text-muted">-</span>
              </template>
            </el-table-column>
            
            <el-table-column prop="deathDate" label="死亡日期" width="120" align="center">
              <template #default="scope">
                <span v-if="scope.row.deathDate">{{ formatDate(scope.row.deathDate) }}</span>
                <span v-else class="text-muted">-</span>
              </template>
            </el-table-column>
            
            <el-table-column prop="parentName" label="父节点" width="120" align="center">
              <template #default="scope">
                <span v-if="scope.row.parentName">{{ scope.row.parentName }}</span>
                <span v-else class="text-muted">根节点</span>
              </template>
            </el-table-column>
            
            <el-table-column prop="relationship" label="关系" width="100" align="center">
              <template #default="scope">
                <el-tag v-if="scope.row.relationship" type="success" size="small">
                  {{ scope.row.relationship }}
                </el-tag>
                <span v-else class="text-muted">-</span>
              </template>
            </el-table-column>
            
            <el-table-column label="年龄" width="100" align="center">
              <template #default="scope">
                <span v-if="scope.row.birthDate">{{ calculateAge(scope.row.birthDate, scope.row.deathDate) }}</span>
                <span v-else class="text-muted">-</span>
              </template>
            </el-table-column>
            
            <el-table-column label="状态" width="100" align="center">
              <template #default="scope">
                <el-tag 
                  :type="scope.row.deathDate ? 'danger' : 'success'" 
                  size="small"
                >
                  {{ scope.row.deathDate ? '已故' : '在世' }}
                </el-tag>
              </template>
            </el-table-column>
            
            <el-table-column label="操作" width="150" align="center" fixed="right">
              <template #default="scope">
                <el-button 
                  type="primary" 
                  size="small" 
                  @click="viewMemberEvents(scope.row)"
                >
                  查看事件
                </el-button>
              </template>
            </el-table-column>
          </el-table>
          
          <div class="table-footer">
            <div class="summary">
              共 {{ members.length }} 位成员
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- 成员详情对话框 -->
    <el-dialog 
      v-model="detailDialogVisible" 
      title="成员详情" 
      width="500px"
      :close-on-click-modal="false"
    >
      <div v-if="selectedMember" class="member-detail">
        <div class="detail-item">
          <label>姓名：</label>
          <span>{{ selectedMember.name }}</span>
        </div>
        <div class="detail-item">
          <label>性别：</label>
          <el-tag :type="selectedMember.gender === '男' ? 'primary' : 'danger'" size="small">
            {{ selectedMember.gender }}
          </el-tag>
        </div>
        <div class="detail-item">
          <label>出生日期：</label>
          <span>{{ selectedMember.birthDate ? formatDate(selectedMember.birthDate) : '-' }}</span>
        </div>
        <div class="detail-item">
          <label>死亡日期：</label>
          <span>{{ selectedMember.deathDate ? formatDate(selectedMember.deathDate) : '-' }}</span>
        </div>
        <div class="detail-item">
          <label>父节点：</label>
          <span>{{ selectedMember.parentName || '根节点' }}</span>
        </div>
        <div class="detail-item">
          <label>关系：</label>
          <el-tag v-if="selectedMember.relationship" type="success" size="small">
            {{ selectedMember.relationship }}
          </el-tag>
          <span v-else>-</span>
        </div>
        <div class="detail-item">
          <label>年龄：</label>
          <span>{{ selectedMember.birthDate ? calculateAge(selectedMember.birthDate, selectedMember.deathDate) : '-' }}</span>
        </div>
        <div class="detail-item">
          <label>状态：</label>
          <el-tag 
            :type="selectedMember.deathDate ? 'danger' : 'success'" 
            size="small"
          >
            {{ selectedMember.deathDate ? '已故' : '在世' }}
          </el-tag>
        </div>
      </div>
      
      <template #footer>
        <el-button @click="detailDialogVisible = false">关闭</el-button>
      </template>
    </el-dialog>

    <!-- 成员事件管理对话框 -->
    <el-dialog 
      v-model="eventDialogVisible" 
      :title="`${selectedMemberName} 的重要事件`" 
      width="800px"
      :close-on-click-modal="false"
    >
      <div class="event-header">
        <el-button type="primary" @click="showAddEventDialog = true">添加事件</el-button>
      </div>
      
      <div class="event-list">
        <div v-if="events.length === 0" class="empty-events">
          <el-empty description="暂无事件记录" />
        </div>
        <el-table v-else :data="events" style="width: 100%; margin-top: 16px;">
          <el-table-column prop="event_date" label="事件日期" width="120" align="center">
            <template #default="scope">
              <span>{{ formatDate(scope.row.event_date) }}</span>
            </template>
          </el-table-column>
          <el-table-column prop="event_type" label="事件类型" width="120" align="center" />
          <el-table-column prop="event_description" label="事件描述" />
          <el-table-column label="操作" width="120" align="center">
            <template #default="scope">
              <el-button type="primary" size="small" @click="editEvent(scope.row)">编辑</el-button>
              <el-button type="danger" size="small" @click="deleteEvent(scope.row)">删除</el-button>
            </template>
          </el-table-column>
        </el-table>
      </div>
    </el-dialog>

    <!-- 添加/编辑事件对话框 -->
    <el-dialog 
      v-model="showAddEventDialog" 
      :title="isEditEvent ? '编辑事件' : '添加事件'" 
      width="500px"
    >
      <el-form :model="eventForm" :rules="eventRules" ref="eventFormRef" label-width="80px">
        <el-form-item label="事件日期" prop="event_date">
          <el-date-picker 
            v-model="eventForm.event_date" 
            type="date" 
            placeholder="选择事件日期" 
            format="YYYY-MM-DD"
            value-format="YYYY-MM-DD"
            style="width: 100%;" 
          />
        </el-form-item>
        <el-form-item label="事件类型" prop="event_type">
          <el-select v-model="eventForm.event_type" placeholder="请选择事件类型" style="width: 100%;">
            <el-option label="生活" value="生活" />
            <el-option label="事业学业" value="事业学业" />
            <el-option label="婚姻家庭" value="婚姻家庭" />
            <el-option label="荣誉" value="荣誉" />
            <el-option label="家族" value="家族" />
            <el-option label="其他" value="其他" />
          </el-select>
        </el-form-item>
        <el-form-item label="事件描述" prop="event_description">
          <el-input 
            v-model="eventForm.event_description" 
            type="textarea" 
            :rows="3" 
            placeholder="请输入事件描述" 
          />
        </el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="showAddEventDialog = false">取消</el-button>
        <el-button type="primary" @click="handleSaveEvent">确定</el-button>
      </template>
    </el-dialog>
  </div>
</template>

<script>
import { familyTreeAPI } from '../api/familyTree.js'
import { familyTableAPI } from '../api/familyTable.js'
import { eventAPI } from '../api/event.js'
import { Refresh } from '@element-plus/icons-vue'

export default {
  name: 'MemberList',
  components: {
    Refresh
  },
  data() {
    return {
      members: [],
      loading: false,
      detailDialogVisible: false,
      selectedMember: null,
      familyTables: [],
      selectedFamilyTableId: null,
      // 事件相关
      eventDialogVisible: false,
      showAddEventDialog: false,
      events: [],
      selectedMemberId: null,
      selectedMemberName: '',
      eventForm: {
        id: null,
        member_id: null,
        event_date: '',
        event_type: '',
        event_description: ''
      },
      eventRules: {
        event_date: [{ required: true, message: '请选择事件日期', trigger: 'change' }],
        event_type: [{ required: true, message: '请选择事件类型', trigger: 'change' }],
        event_description: [{ required: true, message: '请输入事件描述', trigger: 'blur' }]
      },
      eventFormRef: null,
      isEditEvent: false
    }
  },
  computed: {
    userId() {
      return this.$store.getters.user.id || 1
    }
  },
  async mounted() {
    await this.loadFamilyTables()
  },
  methods: {
    async loadFamilyTables() {
      const res = await familyTableAPI.getUserFamilyTables(this.userId)
      if (res.data.success) {
        this.familyTables = res.data.data
        if (this.familyTables.length > 0) {
          this.selectedFamilyTableId = this.familyTables[0].id
          this.loadMembers()
        }
      }
    },
    async onTableChange() {
      this.loadMembers()
    },
    async loadMembers() {
      if (!this.selectedFamilyTableId) return
      this.loading = true
      try {
        const response = await familyTreeAPI.getAllMembers(this.selectedFamilyTableId)
        if (response.data.success) {
          this.members = response.data.data
        } else {
          this.$message.error(response.data.message || '加载成员列表失败')
        }
      } catch (error) {
        this.$message.error('加载成员列表失败，请检查网络连接')
      } finally {
        this.loading = false
      }
    },
    refreshData() {
      this.loadMembers()
    },
    viewMember(member) {
      this.selectedMember = member
      this.detailDialogVisible = true
    },
    viewMemberEvents(member) {
      this.selectedMemberId = member.id
      this.selectedMemberName = member.name
      this.eventDialogVisible = true
      this.loadMemberEvents()
    },
    async loadMemberEvents() {
      try {
        const res = await eventAPI.getMemberEvents(this.selectedMemberId)
        if (res.data.success) {
          this.events = res.data.data || []
        } else {
          this.$message.error(res.data.message || '获取事件列表失败')
        }
      } catch (e) {
        this.$message.error('获取事件列表失败')
      }
    },
    editEvent(event) {
      this.isEditEvent = true
      this.eventForm = { ...event }
      this.showAddEventDialog = true
    },
    async deleteEvent(event) {
      try {
        await this.$confirm('确定要删除这个事件吗？', '提示', {
          type: 'warning'
        })
        const res = await eventAPI.deleteEvent(event.member_id)
        if (res.data.success) {
          this.$message.success('删除成功')
          this.loadMemberEvents()
        } else {
          this.$message.error(res.data.message || '删除失败')
        }
      } catch (e) {
        if (e !== 'cancel') {
          this.$message.error('删除失败')
        }
      }
    },
    handleSaveEvent() {
      this.$refs.eventFormRef.validate(async valid => {
        if (!valid) return
        try {
          this.eventForm.member_id = this.selectedMemberId
          const res = this.isEditEvent 
            ? await eventAPI.updateEvent(this.eventForm)
            : await eventAPI.addEvent(this.eventForm)
          
          if (res.data.success) {
            this.$message.success(this.isEditEvent ? '编辑成功' : '添加成功')
            this.showAddEventDialog = false
            this.loadMemberEvents()
            this.resetEventForm()
          } else {
            this.$message.error(res.data.message || (this.isEditEvent ? '编辑失败' : '添加失败'))
          }
        } catch (e) {
          this.$message.error(this.isEditEvent ? '编辑失败' : '添加失败')
        }
      })
    },
    resetEventForm() {
      this.eventForm = {
        id: null,
        member_id: null,
        event_date: '',
        event_type: '',
        event_description: ''
      }
      this.isEditEvent = false
    },
    formatDate(dateStr) {
      if (!dateStr) return ''
      if (dateStr instanceof Date) {
        const year = dateStr.getFullYear()
        const month = String(dateStr.getMonth() + 1).padStart(2, '0')
        const day = String(dateStr.getDate()).padStart(2, '0')
        return `${year}-${month}-${day}`
      }
      if (typeof dateStr === 'string') {
        const dateOnly = dateStr.split('T')[0].split(' ')[0]
        if (dateOnly.match(/^\d{4}-\d{2}-\d{2}$/)) {
          return dateOnly
        }
        const date = new Date(dateStr)
        if (!isNaN(date.getTime())) {
          const year = date.getFullYear()
          const month = String(date.getMonth() + 1).padStart(2, '0')
          const day = String(date.getDate()).padStart(2, '0')
          return `${year}-${month}-${day}`
        }
      }
      return dateStr.length > 10 ? dateStr.slice(0, 10) : dateStr
    },
    calculateAge(birthDate, deathDate) {
      if (!birthDate) return '-'
      const birth = new Date(birthDate)
      const endDate = deathDate ? new Date(deathDate) : new Date()
      if (isNaN(birth.getTime())) return '-'
      const age = endDate.getFullYear() - birth.getFullYear()
      const monthDiff = endDate.getMonth() - birth.getMonth()
      if (monthDiff < 0 || (monthDiff === 0 && endDate.getDate() < birth.getDate())) {
        return age - 1
      }
      return age
    }
  }
}
</script>

<style scoped>
.member-list {
  padding: 20px;
  height: 100vh;
  overflow: auto;
  background-color: #f5f7fa;
}

.header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
  padding: 20px;
  background: white;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.header h2 {
  margin: 0;
  color: #303133;
  font-size: 24px;
  font-weight: 600;
}

.header-actions {
  display: flex;
  gap: 10px;
}

.content {
  background: white;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  overflow: hidden;
}

.loading {
  padding: 40px;
}

.empty-state {
  padding: 60px 20px;
  text-align: center;
}

.member-table {
  padding: 20px;
}

.member-name {
  font-weight: 600;
  color: #303133;
}

.text-muted {
  color: #909399;
  font-style: italic;
}

.table-footer {
  display: flex;
  justify-content: flex-end;
  padding: 15px 0;
  border-top: 1px solid #ebeef5;
  margin-top: 20px;
}

.summary {
  color: #606266;
  font-size: 14px;
}

.member-detail {
  padding: 20px 0;
}

.detail-item {
  display: flex;
  align-items: center;
  margin-bottom: 15px;
  padding: 10px 0;
  border-bottom: 1px solid #f0f0f0;
}

.detail-item:last-child {
  border-bottom: none;
  margin-bottom: 0;
}

.detail-item label {
  width: 100px;
  font-weight: 600;
  color: #606266;
  margin-right: 15px;
}

.detail-item span {
  color: #303133;
  flex: 1;
}

@media (max-width: 768px) {
  .member-list {
    padding: 10px;
  }
  .header {
    flex-direction: column;
    gap: 15px;
    align-items: stretch;
  }
  .header-actions {
    justify-content: center;
  }
  .member-table {
    padding: 10px;
  }
  .detail-item {
    flex-direction: column;
    align-items: flex-start;
    gap: 5px;
  }
  .detail-item label {
    width: auto;
    margin-right: 0;
  }
}

.event-header {
  margin-bottom: 16px;
}
.event-list {
  min-height: 200px;
}
.empty-events {
  text-align: center;
  padding: 40px 0;
}
</style> 