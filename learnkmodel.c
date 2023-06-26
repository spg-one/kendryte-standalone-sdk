old model:
struct model_header
    {
        uint32_t identifier;
        uint32_t version;
        uint32_t flags;
        model_target target;
        uint32_t constants;
        uint32_t main_mem;
        uint32_t nodes; //4
        uint32_t inputs; //1
        uint32_t outputs; //1
        uint32_t reserved0;
    };
//.=0.x28

//inputs_
struct memory_range
{
    memory_type_t memory_type;
    datatype_t datatype;
    uint32_t start;
    uint32_t size; //0x10
};
//.=0x38

//input_shapes_
using runtime_shape_t = std::array<int, 4>; //{1,1,1,4}
//.=0x48

//outputs_
struct memory_range
{
    memory_type_t memory_type;
    datatype_t datatype;
    uint32_t start; //0x28
    uint32_t size; //0xc
};
//.=0x58

constants_ = { offset, model_header_->constants }; //{0x58,0x118}
//.=0x170

//node_headers_ x4
struct node_header
    {
        runtime_opcode opcode; //0xc
        uint32_t body_size; //0x40
    };

struct node_header
    {
        runtime_opcode opcode; //0x4
        uint32_t body_size; //0x70
    };

struct node_header
    {
        runtime_opcode opcode; //0xc
        uint32_t body_size; //0x40
    };

struct node_header
    {
        runtime_opcode opcode; //0x4
        uint32_t body_size; //0x50
    };
//.=node_body_start_=0x190

struct transpose_options : public simple_node_body<transpose_options>
        {
            memory_range input; //{0,0,0,0xa0}
            memory_range output; //{1,0,0x10,0xa0}
            runtime_shape_t in_shape; //{1,1,0xa,4}
            runtime_shape_t perm; //{0,1,3,2}
        };
//.=0x1d4

struct matmul_options
{
    memory_range input_a;
    memory_range input_b;
    memory_range output;
    int32_t a_rows;
    int32_t a_cols;
    int32_t b_cols;
    value_range<float> fused_activation;
    xtl::span<const float> bias;

    void deserialize(span_reader &reader)
    {
        reader.read(input_a); //{1,0,0x0,0x10}
        reader.read(input_b); //{1,0,0x10,0xa0}
        reader.read(output); //{1,0,0xb0,0x28}
        reader.read(a_rows); //{1}
        reader.read(a_cols); //{4}
        reader.read(b_cols); //{0xa}
        reader.read(fused_activation); //{0,0x7f7ffff}
        reader.read_span(bias, b_cols); 
    }
}
//.=0x23c

struct transpose_options : public simple_node_body<transpose_options>
        {
            memory_range input; //{0,0,0xa0,0x78}
            memory_range output; //{1,0,0x38,0x78}
            runtime_shape_t in_shape; //{1,1,3,0xa}
            runtime_shape_t perm; //{0,1,3,2}
        };
//.=0x280

struct matmul_options
{
    memory_range input_a;
    memory_range input_b;
    memory_range output;
    int32_t a_rows;
    int32_t a_cols;
    int32_t b_cols;
    value_range<float> fused_activation;
    xtl::span<const float> bias;

    void deserialize(span_reader &reader)
    {
        reader.read(input_a); //{1,0,0xb0,0x28}
        reader.read(input_b); //{1,0,0x38,0x78}
        reader.read(output); //{1,0,0x28,0xc}
        reader.read(a_rows); //{1}
        reader.read(a_cols); //{0xa}
        reader.read(b_cols); //{3}
        reader.read(fused_activation); //{0x7f7ffff,0x7f7ffff}
        reader.read_span(bias, b_cols); 
    }
}
//end
