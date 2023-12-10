/*********************************************************
* TrafficMonitor ����ӿ�
* Copyright (C) by Zhong Yang 2021
* zhongyang219@hotmail.com
**********************************************************/
#pragma once

//�����ʾ��Ŀ�Ľӿ�
class IPluginItem
{
public:
    /**
     * @brief   ��ȡ��ʾ��Ŀ������
     * @return  const wchar_t*
     */
    virtual const wchar_t* GetItemName() const = 0;

    /**
     * @brief   ��ȡ��ʾ��Ŀ��ΨһID
     * @return  const wchar_t*
     */
    virtual const wchar_t* GetItemId() const = 0;

    /**
     * @brief   ��ȡ��Ŀ��ǩ���ı�
     * @return  const wchar_t*
     */
    virtual const wchar_t* GetItemLableText() const = 0;

    /**
     * @brief   ��ȡ��Ŀ��ֵ���ı�
     * @detail  ���ڴ˺������ܻᱻƵ�����ã���˲�Ҫ�������ȡ������ݣ�
     *  ������ITMPlugin::DataRequired�����л�ȡ���ݺ󱣴�������Ȼ�������ﷵ�ػ�ȡ����ֵ
     * @return  const wchar_t*
     */
    virtual const wchar_t* GetItemValueText() const = 0;

    /**
     * @brief   ��ȡ��Ŀ��ֵ��ʾ���ı�
     * @detail  �˺������ص��ַ����ĳ��Ȼ����ڼ�����ʾ����Ŀ��
     * @return  const wchar_t*
     */
    virtual const wchar_t* GetItemValueSampleText() const = 0;

    /**
     * @brief   ��ʾ�����Ƿ��ɲ�����л���
     * @detail
     *  �������false�������GetItemLableText��GetItemValueText���ص��ı��������������ʾ������дDrawItem�������������á�
     *  �����д�˺���������true���������дDrawItem��������������ӻ�����ʾ����Ĵ��룬
     *  ��ʱGetItemLableText��GetItemValueText��GetItemValueSampleText�ķ���ֵ�������������
     * @return  bool
     */
    virtual bool IsCustomDraw() const { return false; }

    /**
     * @brief   ��ȡ��ʾ����Ŀ��
     * @detail
     *  ֻ�е�CustomDraw()��������trueʱ��д�˺�������Ч��
     *  ���ص�ֵΪDPIΪ96��100%��ʱ�Ŀ�ȣ����������ݵ�ǰϵͳDPI�������Զ��������Ŵ�
     *  ����㲻��ҪΪ��ͬ��DPI���÷��ز�ͬ��ֵ��
     *  ��Ҫע����ǣ�����ķ���ֵ�������Ի���������Ҫ����С��ȣ�DrawItem�����еĲ���w��ֵ���ܻ�������ֵ
     * @return  int
     */
    virtual int GetItemWidth() const { return 0; }

    /**
     * @brief   �Զ��������ʾ����ĺ�����ֻ�е�CustomDraw()��������trueʱ��д�˺�������Ч
     * @param   void * hDC ��ͼ�������ľ��
     * @param   int x ��ͼ�ľ�������
     * @param   int y
     * @param   int w
     * @param   int h
     * @param   bool dark_mode ��ɫģʽΪtrue��ǳɫģʽΪfalse
     * @return  void
     */
    virtual void DrawItem(void* hDC, int x, int y, int w, int h, bool dark_mode) {}

    /**
     * @brief   ��ȡ��ʾ����Ŀ��
     * @detail
     *  ֻ�е�CustomDraw()��������trueʱ��д�˺�������Ч��
     *  �˺�����GetItemWidth��ͬ��������Ը��ݲ���hDC��������Ҫ�Ŀ�ȣ�
     *  �����ص���ʵ�ʵĿ�ȣ������򲻻���ݵ�ǰϵͳ��DPI�Է���ֵ���зŴ�
     *  ��Ҫע����ǣ�����ķ���ֵ�������Ի���������Ҫ����С��ȣ�DrawItem�����еĲ���w��ֵ���ܻ�������ֵ
     * @param   void * hDC ��ͼ�������ľ��
     * @return  int
     */
    virtual int GetItemWidthEx(void* hDC) const { return 0; }

    /** ����¼������� */
    enum MouseEventType
    {
        MT_LCLICKED,    /**< ����������� */
        MT_RCLICKED,    /**< ���������Ҽ� */
        MT_DBCLICKED,   /**< ˫���������� */
    };

    enum MouseEventFlag
    {
        MF_TASKBAR_WND = 1 << 0,        /**< �Ƿ�Ϊ���������ڵ�����¼� */
    };

    /**
     * @brief   �������ʾ����������¼�ʱ�����������
     * @param   MouseEventType type ����¼�������
     * @param   int x ���ָ�����ڵ�x����
     * @param   int y ���ָ�����ڵ�y����
     * @param   void* hWnd ����������¼��Ĵ��ڵľ���������ڻ����������ڣ�
     * @param   int flag Ϊ����MouseEventFlagö�ٳ��������
     * @return  int ������ط�0������������Ϊ����Ѿ��Դ�����¼�������ȫ������Ӧ�������򽫲����ٶԴ�����¼����������Ӧ��
     *   ���統typeΪMT_RCLICKEDʱ��������򷵻�0����ᵯ���������ṩ���Ҽ��˵��������ط�0ʱ�������򲻻������κδ���
     */
    virtual int OnMouseEvent(MouseEventType type, int x, int y, void* hWnd, int flag) { return 0; }

    enum KeyboardEventFlag
    {
        KF_TASKBAR_WND = 1 << 0,        /**< �Ƿ�Ϊ���������ڵļ����¼� */
    };

    /**
     * @brief   �������ʾ�����м����¼�ʱ�����������
     * @param   int key ���µļ�
     * @param   bool ctrl �Ƿ�����Ctrl��
     * @param   bool shift �Ƿ�����Shift��
     * @param   bool alt �Ƿ�����Alt��
     * @param   void* hWnd �����˼����¼��Ĵ��ڵľ���������ڻ����������ڣ�
     * @param   int flag Ϊ����KeyboardEventFlagö�ٳ��������
     * @return  int ������ط�0������������Ϊ����Ѿ��Դ˼����¼�������ȫ������Ӧ�������򽫲����ٶԴ˼����¼����������Ӧ��
     */
    virtual int OnKeboardEvent(int key, bool ctrl, bool shift, bool alt, void* hWnd, int flag) { return 0; }

    enum ItemInfoType
    {

    };
    virtual void* OnItemInfo(ItemInfoType, void* para1, void* para2) { return 0; }
};


//����ӿ�
class ITMPlugin
{
public:
    /**
     * @brief   ����ӿڵİ汾�������޸��˲���ӿ�ʱ�Ż��޸�����ķ���ֵ��
     * @attention ��������߲�Ӧ���޸�����ķ���ֵ��Ҳ��Ӧ����д���麯����
     * @return  int
     */
    virtual int GetAPIVersion() const { return 5; }

    /**
     * @brief   ��ȡ�����ʾ��Ŀ�Ķ���
     * @detail  һ�����dll�����ṩ���ʵ��IPluginItem�ӿڵĶ��󣬶�Ӧ�����ʾ��Ŀ��
     *  ��index��ֵ���ڻ����0��С��IPluginItem�ӿڵĶ���ĸ���ʱ�����ض����IPluginItem�ӿڵ�ָ�룬�������Ӧ�÷��ؿ�ָ�롣
     *  �������ṩ������ʾ��Ŀ����index����0��1ʱ���ض�ӦIPluginItem�ӿڵĶ�������ֵʱ���뷵�ؿ�ָ�롣
     * @param   int index ���������
     * @return  IPluginItem* �����ʾ��Ŀ�Ķ���
     */
    virtual IPluginItem* GetItem(int index) = 0;

    /**
     * @brief   �������ÿ��һ��ʱ����ô˺����������Ҫ�ں������ȡһ�μ�ص�����
     */
    virtual void DataRequired() = 0;

    /** ѡ�����öԻ���ķ���ֵ */
    enum OptionReturn
    {
        OR_OPTION_CHANGED,          /**< ѡ�����öԻ����и�����ѡ������ */
        OR_OPTION_UNCHANGED,        /**< ѡ�����öԻ�����δ����ѡ������ */
        OR_OPTION_NOT_PROVIDED      /**< δ�ṩѡ�����öԻ��� */
    };

    /**
     * @brief   ��������ô˺����Դ򿪲����ѡ�����öԻ���
     * @detail  �˺�����һ��Ҫ��д���������ṩ��ѡ�����ý��棬��Ӧ����д�˺�����������󷵻�OR_OPTION_CHANGED��OR_OPTION_UNCHANGED��
     * @param   void * hParent �����ڵľ��
     *  ����ֵΪOR_OPTION_NOT_PRVIDED����Ϊ������ṩѡ�����öԻ���
     * @return  ITMPlugin::OptionReturn
     */
    virtual OptionReturn ShowOptionsDialog(void* hParent) { return OR_OPTION_NOT_PROVIDED; }

    /** �����Ϣ������ */
    enum PluginInfoIndex
    {
        TMI_NAME,           /**< ���� */
        TMI_DESCRIPTION,    /**< ���� */
        TMI_AUTHOR,         /**< ���� */
        TMI_COPYRIGHT,      /**< ��Ȩ */
        TMI_VERSION,        /**< �汾 */
        TMI_URL,            /**< ��ҳ */
        TMI_MAX             /**< �����Ϣ�����ֵ */
    };

    /**
     * @brief   ��ȡ�˲������Ϣ������index��ֵ���ض�Ӧ����Ϣ
     */
    virtual const wchar_t* GetInfo(PluginInfoIndex index) = 0;

    /** ������ļ����Ϣ */
    struct MonitorInfo
    {
        unsigned long long up_speed{};
        unsigned long long down_speed{};
        int cpu_usage{};
        int memory_usage{};
        int gpu_usage{};
        int hdd_usage{};
        int cpu_temperature{};
        int gpu_temperature{};
        int hdd_temperature{};
        int main_board_temperature{};
        int cpu_freq{};
    };

    /**
     * @brief   ��������ô˺����������������л�ȡ���ļ����Ϣ
     */
    virtual void OnMonitorInfo(const MonitorInfo& monitor_info) {}

    /**
     * @brief   ��ȡ���Ҫ�������ʾ����ʾ���ı�
     */
    virtual const wchar_t* GetTooltipInfo() { return L""; }

    enum ExtendedInfoIndex
    {
        EI_LABEL_TEXT_COLOR,    //��ͼ�ı�ǩ�ı���ɫ
        EI_VALUE_TEXT_COLOR,    //��ͼ����ֵ�ı���ɫ
        EI_DRAW_TASKBAR_WND,    //�Ƿ��������������

        //������ѡ������
        EI_NAIN_WND_NET_SPEED_SHORT_MODE,   //������ʾ���ģʽ
        EI_MAIN_WND_SPERATE_WITH_SPACE,     //��ֵ�͵�λʹ�ÿո�ָ�
        EI_MAIN_WND_UNIT_BYTE,              //���ٵ�λ�Ƿ�ʹ��B���ֽڣ�
        EI_MAIN_WND_UNIT_SELECT,            //���ٵ�λѡ��0���Զ���1���̶�ΪKB/s��2���̶�ΪMB/s��
        EI_MAIN_WND_NOT_SHOW_UNIT,          //����ʾ���ٵ�λ
        EI_MAIN_WND_NOT_SHOW_PERCENT,       //����ʾ�ٷֺ�

        //��������������
        EI_TASKBAR_WND_NET_SPEED_SHORT_MODE,    //������ʾ���ģʽ
        EI_TASKBAR_WND_SPERATE_WITH_SPACE,      //��ֵ�͵�λʹ�ÿո�ָ�
        EI_TASKBAR_WND_VALUE_RIGHT_ALIGN,       //��ֵ�Ҷ���
        EI_TASKBAR_WND_NET_SPEED_WIDTH,         //�������ݿ��
        EI_TASKBAR_WND_UNIT_BYTE,               //���ٵ�λ�Ƿ�ʹ��B���ֽڣ�
        EI_TASKBAR_WND_UNIT_SELECT,             //���ٵ�λѡ��0���Զ���1���̶�ΪKB/s��2���̶�ΪMB/s��
        EI_TASKBAR_WND_NOT_SHOW_UNIT,           //����ʾ���ٵ�λ
        EI_TASKBAR_WND_NOT_SHOW_PERCENT,        //����ʾ�ٷֺ�

        EI_CONFIG_DIR,                      //�����ļ���Ŀ¼
    };

    /**
     * @brief   ��������ô˺������������ݸ�����Ϣ
     * @param   ExtendedInfoIndex index ��Ϣ�����������������������ݵ���Ϣ
     * @param   const wchar_t* data ���ݵ�����
     * @return  void
     */
    virtual void OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data) {}

    /**
     * @brief   ��ȡ�����ͼ�꣬HICON��ʽ
     */
    virtual void* GetPluginIcon() { return nullptr; }

    /**
     * @brief   ��ȡ��������������
     * @return  int ��������������
     */
    virtual int GetCommandCount() { return 0; }

    /**
     * @brief   ��ȡ�������������
     * @param   int command_index ����������������0��ʼ��С��GetCommandCount()�ķ���ֵ��
     * @return  wchar_t* ������������
     */
    virtual const wchar_t* GetCommandName(int command_index) { return nullptr; }

    /**
     * @brief   ��ȡ���������ͼ��
     * @param   int command_index ����������������0��ʼ��С��GetCommandCount()�ķ���ֵ��
     * @return  void* ��������ͼ�꣬HICON��ʽ
     */
    virtual void* GetCommandIcon(int command_index) { return nullptr; }

    /**
     * @brief   ִ��һ���������ʱ�ɿ�ܵ���
     * @param   int command_index ����������������0��ʼ��С��GetCommandCount()�ķ���ֵ��
     * @param   void* hWnd ���ʹ�����Ĵ��ھ��
     * @param   void* para Ԥ������
     */
    virtual void OnPluginCommand(int command_index, void* hWnd, void* para) {}

    /**
    * @brief   ��ȡ��������Ƿ��ڹ�ѡ״̬
    * @param   int command_index ����������������0��ʼ��С��GetCommandCount()�ķ���ֵ��
    * @return  1���ѹ�ѡ��0��δ��ѡ
    */
    virtual int IsCommandChecked(int command_index) { return false; }

};

/*
* ע�⣺���dll�赼�����º���
* ITMPlugin* TMPluginGetInstance();
*   ��������һ��ITMPlugin�ӿڵĶ����ָ�롣
*   �˶���ͨ��Ӧ��Ϊһ��ȫ�ֻ�̬�Ķ����ڳ������н���ǰ��������Ӧ�ñ��ͷš�
*/