<template>
  <div class="family-table-selector">
    <el-card class="selector-card">
      <template #header>
        <div class="card-header">
          <span>选择家族表</span>
          <el-button type="primary" size="small" @click="showCreateDialog">创建新家族表</el-button>
        </div>
      </template>
      
      <div v-if="familyTables.length === 0" class="empty-state">
        <el-empty description="您还没有创建任何家族表">
          <el-button type="primary" @click="showCreateDialog">创建第一个家族表</el-button>
        </el-empty>
      </div>
      
      <div v-else class="table-list">
        <el-radio-group v-model="selectedTableId" @change="onTableChange">
          <div v-for="table in familyTables" :key="table.id" class="table-item">
            <el-radio :label="table.id">
              <div class="table-info">
                <div class="table-name">{{ table.table_name }}</div>
                <div class="table-content">{{ table.content || '暂无描述' }}</div>
                <div class="table-time">创建时间: {{ formatDate(table.establish_time) }}</div>
              </div>
            </el-radio>
          </div>
        </el-radio-group>
      </div>
    </el-card>

    <!-- 创建家族表对话框 -->
    <el-dialog v-model="createDialogVisible" title="创建新家族表" width="500px">
      <el-form :model="newTable" :rules="tableRules" ref="tableForm" label-width="80px">
        <el-form-item label="表名称" prop="tableName">
          <el-input v-model="newTable.tableName" placeholder="请输入家族表名称" />
        </el-form-item>
        <el-form-item label="描述">
          <el-input v-model="newTable.content" type="textarea" :rows="3" placeholder="请输入家族表描述" />
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <el-button @click="createDialogVisible = false">取消</el-button>
          <el-button type="primary" @click="createTable">确定</el-button>
        </span>
      </template>
    </el-dialog>
  </div>
</template>

<script>
import { familyTableAPI } from '../api/familyTable';

export default {
  name: 'FamilyTableSelector',
  props: {
    userId: {
      type: Number,
      required: true
    }
  },
  data() {
    return {
      familyTables: [],
      selectedTableId: null,
      createDialogVisible: false,
      newTable: {
        tableName: '',
        content: ''
      },
      tableRules: {
        tableName: [
          { required: true, message: '请输入家族表名称', trigger: 'blur' }
        ]
      }
    }
  },
  mounted() {
    this.loadFamilyTables();
  },
  methods: {
    async loadFamilyTables() {
      try {
        const response = await familyTableAPI.getUserFamilyTables(this.userId);
        if (response.data.success) {
          this.familyTables = response.data.data;
          if (this.familyTables.length > 0) {
            this.selectedTableId = this.familyTables[0].id;
            this.$emit('table-selected', this.selectedTableId);
          }
        } else {
          this.$message.error(response.data.message || '加载家族表失败');
        }
      } catch (error) {
        this.$message.error('加载家族表失败，请检查网络连接');
      }
    },

    showCreateDialog() {
      this.createDialogVisible = true;
      this.newTable = {
        tableName: '',
        content: ''
      };
    },

    async createTable() {
      this.$refs.tableForm.validate(async (valid) => {
        if (valid) {
          try {
            const response = await familyTableAPI.createFamilyTable({
              userId: this.userId,
              tableName: this.newTable.tableName,
              content: this.newTable.content
            });

            if (response.data.success) {
              this.$message.success('创建家族表成功');
              this.createDialogVisible = false;
              this.loadFamilyTables(); // 重新加载列表
            } else {
              this.$message.error(response.data.message || '创建家族表失败');
            }
          } catch (error) {
            this.$message.error('创建家族表失败，请检查网络连接');
          }
        }
      });
    },

    onTableChange(tableId) {
      this.$emit('table-selected', tableId);
    },

    formatDate(dateStr) {
      if (!dateStr) return '';
      
      if (typeof dateStr === 'string') {
        const dateOnly = dateStr.split('T')[0].split(' ')[0];
        if (dateOnly.match(/^\d{4}-\d{2}-\d{2}$/)) {
          return dateOnly;
        }
      }
      
      const date = new Date(dateStr);
      if (!isNaN(date.getTime())) {
        const year = date.getFullYear();
        const month = String(date.getMonth() + 1).padStart(2, '0');
        const day = String(date.getDate()).padStart(2, '0');
        return `${year}-${month}-${day}`;
      }
      
      return dateStr;
    }
  }
}
</script>

<style scoped>
.family-table-selector {
  max-width: 600px;
  margin: 0 auto;
}

.selector-card {
  margin: 20px;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.empty-state {
  text-align: center;
  padding: 40px 0;
}

.table-list {
  max-height: 400px;
  overflow-y: auto;
}

.table-item {
  margin-bottom: 15px;
  padding: 15px;
  border: 1px solid #e4e7ed;
  border-radius: 8px;
  transition: all 0.3s ease;
}

.table-item:hover {
  border-color: #409eff;
  background: #f0f9ff;
}

.table-info {
  margin-left: 10px;
}

.table-name {
  font-weight: bold;
  font-size: 16px;
  color: #303133;
  margin-bottom: 5px;
}

.table-content {
  font-size: 14px;
  color: #606266;
  margin-bottom: 5px;
}

.table-time {
  font-size: 12px;
  color: #909399;
}

.dialog-footer {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
}
</style> 