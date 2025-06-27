<template>
  <div class="family-table-manager">
    <div class="header">
      <h2>家谱表管理</h2>
      <el-button type="primary" @click="showCreateDialog = true">新建家谱表</el-button>
    </div>
    <el-table :data="tableList" style="width: 100%; margin-top: 20px;">
      <el-table-column prop="name" label="家谱表名称" align="center" />
      <el-table-column prop="content" label="简介" align="center" />
      <el-table-column prop="createTime" label="创建时间" align="center" />
      <el-table-column label="操作" align="center" width="260">
        <template #default="scope">
          <el-button type="success" size="small" @click="enterTable(scope.row)">进入</el-button>
          <el-button type="primary" size="small" @click="showEdit(scope.row)">编辑</el-button>
          <el-button type="danger" size="small" @click="deleteTable(scope.row)" :loading="deletingId === scope.row.id">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <!-- 新建家谱表对话框 -->
    <el-dialog v-model="showCreateDialog" title="新建家谱表" width="400px">
      <el-form :model="createForm" :rules="createRules" ref="createFormRef" label-width="80px">
        <el-form-item label="名称" prop="name">
          <el-input v-model="createForm.name" placeholder="请输入家谱表名称" />
        </el-form-item>
        <el-form-item label="简介" prop="content">
          <el-input v-model="createForm.content" placeholder="请输入家谱表简介" type="textarea" />
        </el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="showCreateDialog = false">取消</el-button>
        <el-button type="primary" @click="handleCreate">确定</el-button>
      </template>
    </el-dialog>
    <!-- 编辑家谱表对话框 -->
    <el-dialog v-model="showEditDialog" title="编辑家谱表" width="400px">
      <el-form :model="editForm" :rules="createRules" ref="editFormRef" label-width="80px">
        <el-form-item label="名称" prop="name">
          <el-input v-model="editForm.name" placeholder="请输入家谱表名称" />
        </el-form-item>
        <el-form-item label="简介" prop="content">
          <el-input v-model="editForm.content" placeholder="请输入家谱表简介" type="textarea" />
        </el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="showEditDialog = false">取消</el-button>
        <el-button type="primary" @click="handleEdit">保存</el-button>
      </template>
    </el-dialog>
  </div>
</template>

<script>
import { ElMessage, ElMessageBox } from 'element-plus'
import { familyTableAPI } from '../api/familyTable'

export default {
  name: 'FamilyTableManager',
  data() {
    return {
      tableList: [],
      showCreateDialog: false,
      showEditDialog: false,
      createForm: { name: '', content: '' },
      editForm: { id: '', name: '', content: '' },
      createRules: {
        name: [{ required: true, message: '请输入名称', trigger: 'blur' }],
        content: [{ required: true, message: '请输入简介', trigger: 'blur' }]
      },
      createFormRef: null,
      editFormRef: null,
      deletingId: null
    }
  },
  mounted() {
    this.loadTableList()
  },
  methods: {
    async loadTableList() {
      try {
        const userId = this.$store.getters.user.id || 1
        const res = await familyTableAPI.getUserFamilyTables(userId)
        if (res.data.success) {
          this.tableList = res.data.data.map(item => ({
            ...item,
            name: item.tableName || item.table_name || item.name,
            content: item.content,
            createTime: (item.createTime || item.establish_time)
              ? (item.createTime || item.establish_time).toString().slice(0, 10)
              : ''
          }))
        } else {
          ElMessage.error(res.data.message || '获取家谱表列表失败')
        }
      } catch (e) {
        ElMessage.error('获取家谱表列表失败')
      }
    },
    enterTable(row) {
      this.$store.dispatch('setSelectedFamilyTableId', row.id)
      this.$router.push('/family-tree')
    },
    showEdit(row) {
      this.editForm = { id: row.id, name: row.name, content: row.content }
      this.showEditDialog = true
    },
    async handleEdit() {
      this.$refs.editFormRef.validate(async valid => {
        if (!valid) return
        try {
          const res = await familyTableAPI.updateFamilyTable({
            id: this.editForm.id,
            tableName: this.editForm.name,
            content: this.editForm.content
          })
          if (res.data.success) {
            ElMessage.success('编辑成功')
            this.showEditDialog = false
            this.loadTableList()
          } else {
            ElMessage.error(res.data.message || '编辑失败')
          }
        } catch (e) {
          ElMessage.error('编辑失败')
        }
      })
    },
    deleteTable(row) {
      ElMessageBox.confirm(`确定要删除家谱表"${row.name}"吗？此操作不可恢复！`, '提示', {
        type: 'warning',
        confirmButtonText: '删除',
        cancelButtonText: '取消'
      }).then(async () => {
        this.deletingId = row.id
        try {
          const res = await familyTableAPI.deleteFamilyTable(row.id)
          if (res.data.success) {
            ElMessage.success('删除成功')
            this.loadTableList()
          } else {
            ElMessage.error(res.data.message || '删除失败')
          }
        } catch (e) {
          ElMessage.error('删除失败')
        } finally {
          this.deletingId = null
        }
      }).catch(() => {})
    },
    handleCreate() {
      this.$refs.createFormRef.validate(async valid => {
        if (!valid) return
        try {
          const userId = this.$store.getters.user.id || 1
          const res = await familyTableAPI.createFamilyTable({
            tableName: this.createForm.name,
            content: this.createForm.content,
            userId
          })
          if (res.data.success) {
            ElMessage.success('新建成功')
            this.showCreateDialog = false
            this.createForm.name = ''
            this.createForm.content = ''
            this.loadTableList()
          } else {
            ElMessage.error(res.data.message || '新建失败')
          }
        } catch (e) {
          ElMessage.error('新建失败')
        }
      })
    }
  }
}
</script>

<style scoped>
.family-table-manager {
  padding: 32px;
  background: #fff;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.08);
  min-height: 80vh;
}
.header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
}
</style> 