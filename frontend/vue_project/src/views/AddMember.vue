<template>
  <div class="add-member">
    <div class="form-card">
      <h1>增加成员</h1>
      <el-form :model="newMember" :rules="rules" ref="memberForm" label-width="80px" @submit.prevent>
        <el-form-item label="姓名" prop="name">
          <el-input v-model="newMember.name" placeholder="请输入姓名" />
        </el-form-item>
        <el-form-item label="出生日期" prop="dob">
          <el-date-picker 
            v-model="newMember.dob" 
            type="date" 
            placeholder="选择日期" 
            format="YYYY-MM-DD"
            value-format="YYYY-MM-DD"
            style="width: 100%;" 
          />
        </el-form-item>
        <el-form-item label="关系" prop="relationship">
          <el-select v-model="newMember.relationship" placeholder="请选择关系">
            <el-option label="父辈" value="父辈" />
            <el-option label="平辈" value="平辈" />
            <el-option label="子辈" value="子辈" />
          </el-select>
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="addMember">添加成员</el-button>
          <el-button @click="resetForm">重置</el-button>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      newMember: {
        name: '',
        dob: '',
        relationship: '',
      },
      rules: {
        name: [
          { required: true, message: '请输入姓名', trigger: 'blur' },
          { min: 2, max: 10, message: '姓名长度2-10个字', trigger: 'blur' }
        ],
        dob: [
          { required: true, message: '请选择出生日期', trigger: 'change' }
        ],
        relationship: [
          { required: true, message: '请选择关系', trigger: 'change' }
        ]
      }
    };
  },
  methods: {
    addMember() {
      this.$refs.memberForm.validate((valid) => {
        if (valid) {
          // 这里可以将新成员数据保存到数据库或者本地状态中
          this.$message.success('成员已添加');
          this.resetForm();
        }
      });
    },
    resetForm() {
      this.$refs.memberForm.resetFields();
    }
  }
};
</script>

<style scoped>
.add-member {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 80vh;
  background: none;
}
.form-card {
  width: 430px;
  padding: 30px 20px 20px 20px;
  box-shadow: 0 2px 12px rgba(0,0,0,0.08);
  border-radius: 12px;
}
h1 {
  text-align: center;
  margin-bottom: 20px;
}
</style>
