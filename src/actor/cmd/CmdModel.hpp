/*******************************************************************************
 * Project:  Nebula
 * @file     CmdModel.hpp
 * @brief 
 * @author   bwar
 * @date:    Apr 4, 2018
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_ACTOR_CMD_CMDMODEL_HPP_
#define SRC_ACTOR_CMD_CMDMODEL_HPP_

#include "actor/Actor.hpp"

namespace neb
{

class CmdModel: public Actor
{
public:
    CmdModel(int32 iCmd)
        : Actor(Actor::ACT_CMD, gc_dNoTimeout),
          m_iCmd(iCmd)
    {
    }
    CmdModel(const CmdModel&) = delete;
    CmdModel& operator=(const CmdModel&) = delete;
    virtual ~CmdModel(){};

    /**
     * @brief 初始化Cmd
     * @note Cmd类实例初始化函数，大部分Cmd不需要初始化，需要初始化的Cmd可派生后实现此函数，
     * 在此函数里可以读取配置文件（配置文件必须为json格式）。配置文件由Cmd的设计者自行定义，
     * 存放于conf/目录，配置文件名最好与Cmd名字保持一致，加上.json后缀。配置文件的更新同步
     * 会由框架自动完成。
     * @return 是否初始化成功
     */
    virtual bool Init()
    {
        return(true);
    }

    /**
     * @brief 命令处理入口
     * @note 框架层成功解析数据包后，根据MsgHead里的Cmd找到对应的Cmd类实例调用将数据包及
     * 数据包来源tagChannelContext传给AnyMessage处理。若处理过程不涉及网络IO之类需异步处
     * 理的耗时调用，则无需新创建Step类实例来处理。若处理过程涉及耗时异步调用，则应创建Step
     * 类实例，并向框架层注册Step类实例，调用Step.Start()后即返回。
     * @param stCtx 消息来源上下文
     * @param oMsgHead 数据包头
     * @param oMsgBody 数据包体
     * @return 命令是否处理成功
     */
    virtual bool AnyMessage(
                    std::shared_ptr<SocketChannel> pChannel,
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody) = 0;

protected:
    int GetCmd() const
    {
        return(m_iCmd);
    }

private:
    int32 m_iCmd;
    friend class WorkerImpl;
};

} /* namespace neb */

#endif /* SRC_ACTOR_CMD_CMDMODEL_HPP_ */
