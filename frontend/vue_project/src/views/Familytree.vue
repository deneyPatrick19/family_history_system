<template>
  <div class="family-tree">
    <el-dialog v-model="showCreateTableDialog" title="新建家谱表" width="400px" :close-on-click-modal="false">
      <el-form :model="createTableForm" :rules="createTableRules" ref="createTableFormRef" label-width="80px">
        <el-form-item label="名称" prop="name">
          <el-input v-model="createTableForm.name" placeholder="请输入家谱表名称" />
        </el-form-item>
        <el-form-item label="内容" prop="content">
          <el-input v-model="createTableForm.content" placeholder="请输入家谱表内容" type="textarea" />
        </el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="showCreateTableDialog = false">取消</el-button>
        <el-button type="primary" @click="handleCreateTable">确定</el-button>
      </template>
    </el-dialog>
    <!-- 删除家族表选择器相关内容，直接显示家谱树管理界面 -->
    <div class="tree-management">
      <div class="tree-header">
        <div class="header-left">
          <h2>家族树管理</h2>
        </div>
        <div class="header-actions">
          <el-button type="primary" @click="addRootNode">添加根节点</el-button>
          <el-button 
            type="success" 
            @click="addPerson"
            :disabled="!rootNode || hasAddedPerson"
            :title="!rootNode ? '请先添加根节点' : hasAddedPerson ? '已添加过个人，不允许再次添加' : '增加个人'"
          >增加个人</el-button>
          <el-button type="info" @click="refreshTree">刷新数据</el-button>
          <el-button type="warning" @click="viewMemberList">查看成员列表</el-button>
        </div>
      </div>
      <div class="tree-container">
        <div class="tree-wrapper">
          <FamilyNode
            v-if="rootNode"
            :node="rootNode"
            :selectedNode="selectedNode"
            :selectNode="selectNode"
            :addChild="addChild"
            :addParent="addParent"
            :viewNode="viewNode"
            :deleteNode="deleteNode"
            :formatDate="formatDate"
          />
          <div v-else class="empty-tree">
            <el-empty description="暂无家族树数据，请添加根节点开始创建">
              <el-button type="primary" @click="addRootNode">添加根节点</el-button>
            </el-empty>
          </div>
        </div>
      </div>
    </div>

    <!-- 节点编辑对话框 -->
    <el-dialog v-model="dialogVisible" :title="dialogTitle" width="500px">
      <el-form :model="editingNode" :rules="nodeRules" ref="nodeForm" label-width="80px">
        <el-form-item label="姓名" prop="name">
          <el-input v-model="editingNode.name" placeholder="请输入姓名" :disabled="isViewMode" />
        </el-form-item>
        <el-form-item v-if="dialogTitle === '增加个人'" label="父节点" prop="parentId">
          <el-select v-model="editingNode.parentId" placeholder="请选择父节点" style="width: 100%;" @change="onParentChange" :disabled="isViewMode">
            <el-option 
              v-for="node in getAllNodes()" 
              :key="node.id" 
              :label="node.name" 
              :value="node.id" 
            />
          </el-select>
        </el-form-item>
        <el-form-item v-if="dialogTitle === '增加个人'" label="使用保存信息">
          <el-button 
            type="info" 
            size="small" 
            @click="loadSavedInfo"
            :disabled="!hasSavedInfo() || isViewMode"
          >使用已保存的个人信息</el-button>
        </el-form-item>
        <el-form-item label="出生日期" prop="birthDate">
          <el-date-picker 
            v-model="editingNode.birthDate" 
            type="date" 
            placeholder="选择出生日期" 
            format="YYYY-MM-DD"
            value-format="YYYY-MM-DD"
            style="width: 100%;" 
            :disabled="isViewMode"
          />
        </el-form-item>
        <el-form-item label="死亡日期">
          <el-date-picker 
            v-model="editingNode.deathDate" 
            type="date" 
            placeholder="选择死亡日期" 
            format="YYYY-MM-DD"
            value-format="YYYY-MM-DD"
            style="width: 100%;" 
            :disabled="isViewMode"
          />
        </el-form-item>
        <el-form-item label="性别" prop="gender">
          <el-select v-model="editingNode.gender" placeholder="请选择性别" style="width: 100%;" :disabled="isViewMode">
            <el-option label="男" value="男" />
            <el-option label="女" value="女" />
          </el-select>
        </el-form-item>
        <el-form-item label="关系" prop="relationship">
          <el-select v-model="editingNode.relationship" placeholder="请选择关系" style="width: 100%;" :disabled="isViewMode">
            <el-option label="父亲" value="父亲" />
            <el-option label="母亲" value="母亲" />
            <el-option label="儿子" value="儿子" />
            <el-option label="女儿" value="女儿" />
          </el-select>
        </el-form-item>
        <el-form-item label="生平简介">
          <el-input v-model="editingNode.bio" type="textarea" :rows="3" placeholder="请输入生平简介" :disabled="isViewMode" />
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <el-button @click="dialogVisible = false">取消</el-button>
          <el-button v-if="isViewMode" type="primary" @click="enableEdit">编辑</el-button>
          <el-button v-else type="primary" @click="saveNode">确定</el-button>
        </span>
      </template>
    </el-dialog>
  </div>
</template>

<script>
import FamilyNode from '../components/FamilyNode.vue';
import { familyTreeAPI } from '../api/familyTree';
import { familyTableAPI } from '../api/familyTable';

export default {
  name: 'FamilyTree',
  components: { FamilyNode },
  data() {
    return {
      userId: 1,
      rootNode: null,
      selectedNode: null,
      dialogVisible: false,
      dialogTitle: '添加节点',
      editingNode: {
        name: '',
        birthDate: '',
        deathDate: '',
        gender: '男',
        relationship: '',
        bio: ''
      },
      nodeRules: {
        name: [
          { required: true, message: '请输入姓名', trigger: 'blur' }
        ],
        birthDate: [
          { required: true, message: '请选择出生日期', trigger: 'change' }
        ],
        gender: [
          { required: true, message: '请选择性别', trigger: 'change' }
        ],
        relationship: [
          { required: true, message: '请选择关系', trigger: 'change' }
        ]
      },
      loading: false,
      hasAddedPerson: false,
      isViewMode: true,
      showCreateTableDialog: false,
      createTableForm: { name: '', content: '' },
      createTableRules: {
        name: [{ required: true, message: '请输入名称', trigger: 'blur' }],
        content: [{ required: true, message: '请输入内容', trigger: 'blur' }]
      },
      createTableFormRef: null
    }
  },
  computed: {
    selectedFamilyTableId() {
      return this.$store.getters.selectedFamilyTableId
    }
  },
  mounted() {
    const user = this.$store.getters.user;
    if (user && user.id) {
      this.userId = user.id;
    }
    // 优先从store/localStorage恢复ID，否则自动选中第一个家谱表
    if (!this.selectedFamilyTableId) {
      this.trySelectFirstFamilyTable();
    } else {
      this.loadTreeData();
    }
  },
  methods: {
    async handleCreateTable() {
      this.$refs.createTableFormRef.validate(async valid => {
        if (!valid) return;
        try {
          const res = await familyTableAPI.createFamilyTable({
            tableName: this.createTableForm.name,
            content: this.createTableForm.content,
            userId: this.userId
          });
          if (res.data.success) {
            this.$message.success('新建家谱表成功');
            this.showCreateTableDialog = false;
            this.createTableForm.name = '';
            this.createTableForm.content = '';
            // 设置store中的家谱表ID，并加载树数据
            this.$store.dispatch('setSelectedFamilyTableId', res.data.tableId);
            this.loadTreeData();
          } else {
            this.$message.error(res.data.message || '新建家谱表失败');
          }
        } catch (e) {
          this.$message.error('新建家谱表失败');
        }
      });
    },
    async trySelectFirstFamilyTable() {
      // 获取用户所有家谱表，自动选中第一个
      try {
        const res = await this.$api.familyTableAPI.getUserFamilyTables(this.userId);
        if (res.data.success && res.data.data.length > 0) {
          const firstTableId = res.data.data[0].id;
          this.$store.dispatch('setSelectedFamilyTableId', firstTableId);
          this.loadTreeData();
        } else {
          this.showCreateTableDialog = true;
        }
      } catch (e) {
        this.showCreateTableDialog = true;
      }
    },
    // 从后端加载树形数据
    async loadTreeData() {
      if (!this.selectedFamilyTableId) return;
      this.loading = true;
      try {
        const response = await familyTreeAPI.getFamilyTree(this.selectedFamilyTableId);
        if (response.data.success) {
          const treeData = response.data.data;
          if (treeData && treeData.length > 0) {
            this.rootNode = treeData[0];
            this.mapBioField(this.rootNode);
          } else {
            this.rootNode = null;
          }
          this.hasAddedPerson = false;
        } else {
          this.$message.error(response.data.message || '加载家谱树失败');
        }
      } catch (error) {
        this.$message.error('加载家谱树失败，请检查网络连接');
      } finally {
        this.loading = false;
      }
    },
    mapBioField(node) {
      // 递归处理所有节点，确保bio属性存在
      if (node && node.bio === undefined && node.icon !== undefined) {
        node.bio = node.icon;
      }
      if (node && node.children && node.children.length > 0) {
        node.children.forEach(child => this.mapBioField(child));
      }
    },
    // 刷新数据
    refreshTree() {
      this.loadTreeData();
    },

    // 添加根节点
    addRootNode() {
      this.dialogTitle = '添加根节点';
      this.editingNode = {
        name: '',
        birthDate: '',
        deathDate: '',
        gender: '男',
        relationship: '父亲',
        bio: ''
      };
      this.isViewMode = false; // 设置为编辑模式
      this.dialogVisible = true;
    },

    // 增加个人
    addPerson() {
      this.dialogTitle = '增加个人';
      
      // 获取MemberHistory中保存的信息
      const savedMember = this.getSavedMemberInfo();
      
      this.editingNode = {
        name: savedMember.name || '',
        birthDate: savedMember.dob || '', // MemberHistory中使用dob字段
        deathDate: savedMember.deathDate || '',
        gender: savedMember.gender || '男',
        relationship: '儿子', // 默认关系
        bio: savedMember.bio || '',
        parentId: this.rootNode.id // 默认选择根节点作为父节点
      };
      this.isViewMode = false; // 设置为编辑模式
      this.dialogVisible = true;
      
      // 如果有保存的信息，显示提示
      if (this.hasSavedInfo()) {
        this.$message.info('已自动填充保存的个人信息，您可以修改或直接使用');
      }
    },

    // 添加子节点
    addChild(parentNode) {
      this.dialogTitle = '添加子节点';
      // 根据父节点性别自动设置关系
      const defaultRelationship = parentNode.gender === '男' ? '儿子' : '女儿';
      this.editingNode = {
        name: '',
        birthDate: '',
        deathDate: '',
        gender: '男',
        relationship: defaultRelationship,
        bio: '',
        parentId: parentNode.id
      };
      this.isViewMode = false; // 设置为编辑模式
      this.dialogVisible = true;
    },

    // 添加父节点
    async addParent(node) {
      try {
        // 先检查节点是否已经有父节点
        const response = await familyTreeAPI.checkParent(node.id);
        if (response.data.success && response.data.hasParent) {
          this.$message.warning(`该节点已经有父节点: ${response.data.parentName}，每个节点只能有一个父节点`);
          return;
        }
        
        this.dialogTitle = '添加父节点';
        // 根据子节点性别自动设置关系
        const defaultRelationship = node.gender === '男' ? '父亲' : '母亲';
        this.editingNode = {
          name: '',
          birthDate: '',
          deathDate: '',
          gender: '男',
          relationship: defaultRelationship,
          bio: '',
          childId: node.id
        };
        this.isViewMode = false; // 设置为编辑模式
        this.dialogVisible = true;
      } catch (error) {
        this.$message.error('检查父节点失败，请检查网络连接');
      }
    },

    // 查看节点
    viewNode(node) {
      this.dialogTitle = '查看节点信息';
      this.editingNode = { ...node };
      this.isViewMode = true; // 设置为查看模式
      this.dialogVisible = true;
    },

    // 删除节点
    deleteNode(node) {
      this.$confirm('确定要删除这个节点吗？删除后其所有子节点也会被删除。', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(async () => {
        try {
          const response = await familyTreeAPI.deleteNode({
            id: node.id
          });
          
          if (response.data.success) {
            this.$message.success('删除成功');
            this.loadTreeData(); // 重新加载数据
          } else {
            this.$message.error(response.data.message || '删除失败');
          }
        } catch (error) {
          this.$message.error('删除节点失败，请检查网络连接');
        }
      }).catch(() => {
        // 取消删除
      });
    },

    // 保存节点
    async saveNode() {
      this.$refs.nodeForm.validate(async (valid) => {
        if (valid) {
          try {
            let response;
            const nodeData = {
              familyTableId: this.selectedFamilyTableId,
              name: this.editingNode.name,
              gender: this.editingNode.gender,
              birthDate: this.editingNode.birthDate,
              deathDate: this.editingNode.deathDate,
              relationship: this.editingNode.relationship,
              bio: this.editingNode.bio // 新增bio属性
            };
            if (this.editingNode.id) {
              nodeData.id = this.editingNode.id;
              response = await familyTreeAPI.updateNode(nodeData);
            } else {
              if (this.editingNode.parentId) {
                nodeData.parentId = this.editingNode.parentId;
              }
              if (this.editingNode.childId) {
                nodeData.childId = this.editingNode.childId;
              }
              response = await familyTreeAPI.saveNode(nodeData);
            }
            if (response.data.success) {
              this.$message.success('保存成功');
              this.dialogVisible = false;
              if (this.dialogTitle === '增加个人') {
                this.hasAddedPerson = true;
              }
              this.loadTreeData();
            } else {
              this.$message.error(response.data.message || '保存失败');
            }
          } catch (error) {
            this.$message.error('保存节点失败，请检查网络连接');
          }
        }
      });
    },

    // 选择节点
    selectNode(node) {
      this.selectedNode = node;
    },

    formatDate(dateStr) {
      if (!dateStr) return '';
      
      // 如果是Date对象，转换为字符串
      if (dateStr instanceof Date) {
        const year = dateStr.getFullYear();
        const month = String(dateStr.getMonth() + 1).padStart(2, '0');
        const day = String(dateStr.getDate()).padStart(2, '0');
        return `${year}-${month}-${day}`;
      }
      
      // 如果是字符串，尝试解析并格式化
      if (typeof dateStr === 'string') {
        // 移除可能的时间部分
        const dateOnly = dateStr.split('T')[0].split(' ')[0];
        
        // 检查是否是有效的日期格式
        if (dateOnly.match(/^\d{4}-\d{2}-\d{2}$/)) {
          return dateOnly;
        }
        
        // 尝试解析其他格式的日期
        const date = new Date(dateStr);
        if (!isNaN(date.getTime())) {
          const year = date.getFullYear();
          const month = String(date.getMonth() + 1).padStart(2, '0');
          const day = String(date.getDate()).padStart(2, '0');
          return `${year}-${month}-${day}`;
        }
      }
      
      // 如果无法解析，返回原字符串的前10位（兼容旧数据）
      return dateStr.length > 10 ? dateStr.slice(0, 10) : dateStr;
    },

    onParentChange(parentId) {
      this.editingNode.parentId = parentId;
      // 根据选择的父节点自动设置关系
      if (parentId) {
        const parentNode = this.getAllNodes().find(node => node.id === parentId);
        if (parentNode) {
          const defaultRelationship = parentNode.gender === '男' ? '儿子' : '女儿';
          this.editingNode.relationship = defaultRelationship;
        }
      }
    },

    getAllNodes() {
      const nodes = [];
      
      const collectNodes = (node) => {
        if (node) {
          nodes.push(node);
          if (node.children && node.children.length > 0) {
            node.children.forEach(child => collectNodes(child));
          }
        }
      };
      
      if (this.rootNode) {
        collectNodes(this.rootNode);
      }
      
      return nodes;
    },

    // 获取MemberHistory中保存的成员信息
    getSavedMemberInfo() {
      // 优先从store获取
      const storeMembers = this.$store.getters.members;
      if (storeMembers && storeMembers.length > 0) {
        return storeMembers[0];
      }
      
      // 如果store中没有，从localStorage获取
      const saved = localStorage.getItem('member');
      if (saved) {
        try {
          return JSON.parse(saved);
        } catch (error) {
          console.error('解析保存的成员信息失败:', error);
        }
      }
      
      // 如果都没有，返回空对象
      return {
        name: '',
        dob: '',
        gender: '男',
        deathDate: '',
        bio: ''
      };
    },

    // 加载保存的信息
    loadSavedInfo() {
      const savedMember = this.getSavedMemberInfo();
      this.editingNode = {
        ...this.editingNode, // 保持当前的其他字段（如parentId）
        name: savedMember.name || '',
        birthDate: savedMember.dob || '',
        deathDate: savedMember.deathDate || '',
        gender: savedMember.gender || '男',
        bio: savedMember.bio || ''
      };
      this.$message.success('已加载保存的个人信息');
    },

    // 检查是否有保存的信息
    hasSavedInfo() {
      const savedMember = this.getSavedMemberInfo();
      // 检查是否有任何字段有值
      return savedMember.name || savedMember.dob || savedMember.deathDate || savedMember.bio;
    },

    // 启用编辑模式
    enableEdit() {
      this.isViewMode = false;
    },

    // 查看成员列表
    viewMemberList() {
      this.$router.push('/member-list');
    }
  }
}
</script>

<style scoped>
.family-tree {
  padding: 20px;
  height: 100vh;
  overflow: auto;
}

.tree-management {
  height: 100%;
}

.tree-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
  padding-bottom: 15px;
  border-bottom: 1px solid #e4e7ed;
}

.header-left {
  display: flex;
  align-items: center;
  gap: 15px;
}

.tree-header h2 {
  margin: 0;
  color: #303133;
}

.header-actions {
  display: flex;
  gap: 10px;
}

.tree-container {
  min-height: 500px;
  background: #fafafa;
  border-radius: 8px;
  padding: 20px;
  overflow-x: auto;
  overflow-y: auto;
}

.tree-wrapper {
  display: flex;
  justify-content: center;
  min-width: fit-content;
  min-height: fit-content;
  max-height: 100%;
  overflow-y: auto;
}

.tree-node {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.node-content {
  display: flex;
  align-items: center;
  background: white;
  border: 2px solid #e4e7ed;
  border-radius: 8px;
  padding: 15px;
  margin: 10px;
  min-width: 300px;
  cursor: pointer;
  transition: all 0.3s ease;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.node-content:hover {
  border-color: #409eff;
  box-shadow: 0 4px 8px rgba(0,0,0,0.15);
}

.node-content.selected {
  border-color: #409eff;
  background: #f0f9ff;
}

.node-avatar {
  margin-right: 15px;
}

.node-info {
  flex: 1;
  min-width: 0;
}

.node-name {
  font-weight: bold;
  font-size: 16px;
  color: #303133;
  margin-bottom: 5px;
}

.node-details {
  font-size: 12px;
  color: #909399;
}

.node-actions {
  display: flex;
  gap: 5px;
  margin-left: 15px;
}

.children-container {
  position: relative;
  margin-top: 20px;
}

.children-container::before {
  content: '';
  position: absolute;
  top: -10px;
  left: 50%;
  width: 2px;
  height: 10px;
  background: #e4e7ed;
}

.children-wrapper {
  display: flex;
  gap: 40px;
  position: relative;
}

.children-wrapper::before {
  content: '';
  position: absolute;
  top: -10px;
  left: 0;
  right: 0;
  height: 2px;
  background: #e4e7ed;
}

.child-node {
  position: relative;
}

.child-node::before {
  content: '';
  position: absolute;
  top: -10px;
  left: 50%;
  width: 2px;
  height: 10px;
  background: #e4e7ed;
}

.grandchild-node .node-content {
  min-width: 250px;
  padding: 10px;
}

.empty-tree {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 400px;
}

.dialog-footer {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
}
</style>