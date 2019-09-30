namespace QATools
{
    partial class CenposQA
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CenposQA));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.btnRunWsProd = new System.Windows.Forms.Button();
            this.btnRunBridgeProd = new System.Windows.Forms.Button();
            this.btnRunBridgeQa = new System.Windows.Forms.Button();
            this.btnRunWsQa = new System.Windows.Forms.Button();
            this.btnStoreSession = new System.Windows.Forms.Button();
            this.btnClearSession = new System.Windows.Forms.Button();
            this.btnLoadWs = new System.Windows.Forms.Button();
            this.btnLoadBridgeQa = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtCurrentPath = new System.Windows.Forms.TextBox();
            this.txtBridgeVersion = new System.Windows.Forms.TextBox();
            this.txtCurrentSession = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lblVersion = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.btnRunWsProd);
            this.groupBox1.Controls.Add(this.btnRunBridgeProd);
            this.groupBox1.Controls.Add(this.btnRunBridgeQa);
            this.groupBox1.Controls.Add(this.btnRunWsQa);
            this.groupBox1.Controls.Add(this.btnStoreSession);
            this.groupBox1.Controls.Add(this.btnClearSession);
            this.groupBox1.Controls.Add(this.btnLoadWs);
            this.groupBox1.Controls.Add(this.btnLoadBridgeQa);
            this.groupBox1.Location = new System.Drawing.Point(12, 128);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(405, 211);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Available Options";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(115, 94);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(72, 13);
            this.label13.TabIndex = 27;
            this.label13.Text = "Save Session";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(12, 94);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(71, 13);
            this.label12.TabIndex = 26;
            this.label12.Text = "Clear Session";
            this.label12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(320, 192);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(73, 13);
            this.label10.TabIndex = 24;
            this.label10.Text = "Run Prod WS";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(210, 192);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(85, 13);
            this.label9.TabIndex = 22;
            this.label9.Text = "Run Prod Bridge";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(117, 192);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(66, 13);
            this.label7.TabIndex = 20;
            this.label7.Text = "Run QA WS";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(322, 94);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "Load QA WS";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(212, 94);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(82, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "Load QA Bridge";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 192);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(78, 13);
            this.label6.TabIndex = 19;
            this.label6.Text = "Run QA Bridge";
            // 
            // btnRunWsProd
            // 
            this.btnRunWsProd.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnRunWsProd.BackgroundImage")));
            this.btnRunWsProd.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnRunWsProd.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRunWsProd.Location = new System.Drawing.Point(317, 116);
            this.btnRunWsProd.Name = "btnRunWsProd";
            this.btnRunWsProd.Size = new System.Drawing.Size(75, 73);
            this.btnRunWsProd.TabIndex = 16;
            this.btnRunWsProd.Text = "WS";
            this.btnRunWsProd.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            this.btnRunWsProd.UseVisualStyleBackColor = true;
            this.btnRunWsProd.Click += new System.EventHandler(this.btnRunWsProd_Click);
            // 
            // btnRunBridgeProd
            // 
            this.btnRunBridgeProd.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnRunBridgeProd.BackgroundImage")));
            this.btnRunBridgeProd.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnRunBridgeProd.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRunBridgeProd.Location = new System.Drawing.Point(215, 116);
            this.btnRunBridgeProd.Name = "btnRunBridgeProd";
            this.btnRunBridgeProd.Size = new System.Drawing.Size(75, 73);
            this.btnRunBridgeProd.TabIndex = 13;
            this.btnRunBridgeProd.Text = "Bridge";
            this.btnRunBridgeProd.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            this.btnRunBridgeProd.UseVisualStyleBackColor = true;
            this.btnRunBridgeProd.Click += new System.EventHandler(this.btnRunBridgeProd_Click);
            // 
            // btnRunBridgeQa
            // 
            this.btnRunBridgeQa.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnRunBridgeQa.BackgroundImage")));
            this.btnRunBridgeQa.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnRunBridgeQa.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRunBridgeQa.Location = new System.Drawing.Point(11, 116);
            this.btnRunBridgeQa.Name = "btnRunBridgeQa";
            this.btnRunBridgeQa.Size = new System.Drawing.Size(75, 73);
            this.btnRunBridgeQa.TabIndex = 3;
            this.btnRunBridgeQa.Text = "Bridge";
            this.btnRunBridgeQa.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            this.btnRunBridgeQa.UseVisualStyleBackColor = true;
            this.btnRunBridgeQa.Click += new System.EventHandler(this.btnRunBridgeQa_Click);
            // 
            // btnRunWsQa
            // 
            this.btnRunWsQa.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnRunWsQa.BackgroundImage")));
            this.btnRunWsQa.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnRunWsQa.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRunWsQa.Location = new System.Drawing.Point(113, 116);
            this.btnRunWsQa.Name = "btnRunWsQa";
            this.btnRunWsQa.Size = new System.Drawing.Size(75, 73);
            this.btnRunWsQa.TabIndex = 4;
            this.btnRunWsQa.Text = "WS";
            this.btnRunWsQa.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            this.btnRunWsQa.UseVisualStyleBackColor = true;
            this.btnRunWsQa.Click += new System.EventHandler(this.btnRunWsQa_Click);
            // 
            // btnStoreSession
            // 
            this.btnStoreSession.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnStoreSession.BackgroundImage")));
            this.btnStoreSession.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnStoreSession.Location = new System.Drawing.Point(113, 18);
            this.btnStoreSession.Name = "btnStoreSession";
            this.btnStoreSession.Size = new System.Drawing.Size(75, 73);
            this.btnStoreSession.TabIndex = 7;
            this.btnStoreSession.UseVisualStyleBackColor = true;
            this.btnStoreSession.Click += new System.EventHandler(this.btnStoreSession_Click);
            // 
            // btnClearSession
            // 
            this.btnClearSession.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnClearSession.BackgroundImage")));
            this.btnClearSession.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnClearSession.Location = new System.Drawing.Point(10, 18);
            this.btnClearSession.Name = "btnClearSession";
            this.btnClearSession.Size = new System.Drawing.Size(75, 73);
            this.btnClearSession.TabIndex = 6;
            this.btnClearSession.UseVisualStyleBackColor = true;
            this.btnClearSession.Click += new System.EventHandler(this.btnClearSession_Click);
            // 
            // btnLoadWs
            // 
            this.btnLoadWs.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnLoadWs.BackgroundImage")));
            this.btnLoadWs.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnLoadWs.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLoadWs.Location = new System.Drawing.Point(319, 18);
            this.btnLoadWs.Name = "btnLoadWs";
            this.btnLoadWs.Size = new System.Drawing.Size(75, 73);
            this.btnLoadWs.TabIndex = 1;
            this.btnLoadWs.Text = "WS";
            this.btnLoadWs.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            this.btnLoadWs.UseVisualStyleBackColor = true;
            this.btnLoadWs.Click += new System.EventHandler(this.btnLoadWs_Click);
            // 
            // btnLoadBridgeQa
            // 
            this.btnLoadBridgeQa.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnLoadBridgeQa.BackgroundImage")));
            this.btnLoadBridgeQa.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnLoadBridgeQa.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLoadBridgeQa.Location = new System.Drawing.Point(216, 18);
            this.btnLoadBridgeQa.Name = "btnLoadBridgeQa";
            this.btnLoadBridgeQa.Size = new System.Drawing.Size(75, 73);
            this.btnLoadBridgeQa.TabIndex = 0;
            this.btnLoadBridgeQa.Text = "Bridge";
            this.btnLoadBridgeQa.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            this.btnLoadBridgeQa.UseVisualStyleBackColor = true;
            this.btnLoadBridgeQa.Click += new System.EventHandler(this.btnLoadBridgeQa_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Current path:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Bridge version:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(76, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Session name:";
            // 
            // txtCurrentPath
            // 
            this.txtCurrentPath.Location = new System.Drawing.Point(115, 25);
            this.txtCurrentPath.Name = "txtCurrentPath";
            this.txtCurrentPath.ReadOnly = true;
            this.txtCurrentPath.Size = new System.Drawing.Size(289, 20);
            this.txtCurrentPath.TabIndex = 4;
            // 
            // txtBridgeVersion
            // 
            this.txtBridgeVersion.Location = new System.Drawing.Point(115, 55);
            this.txtBridgeVersion.Name = "txtBridgeVersion";
            this.txtBridgeVersion.ReadOnly = true;
            this.txtBridgeVersion.Size = new System.Drawing.Size(289, 20);
            this.txtBridgeVersion.TabIndex = 5;
            // 
            // txtCurrentSession
            // 
            this.txtCurrentSession.Location = new System.Drawing.Point(115, 88);
            this.txtCurrentSession.Name = "txtCurrentSession";
            this.txtCurrentSession.Size = new System.Drawing.Size(289, 20);
            this.txtCurrentSession.TabIndex = 6;
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(12, 11);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(405, 108);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "General Information";
            // 
            // lblVersion
            // 
            this.lblVersion.AutoSize = true;
            this.lblVersion.ForeColor = System.Drawing.SystemColors.ControlDark;
            this.lblVersion.Location = new System.Drawing.Point(352, 342);
            this.lblVersion.Name = "lblVersion";
            this.lblVersion.Size = new System.Drawing.Size(52, 13);
            this.lblVersion.TabIndex = 9;
            this.lblVersion.Text = "v1.0.0.13";
            // 
            // CenposQA
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(429, 356);
            this.Controls.Add(this.lblVersion);
            this.Controls.Add(this.txtCurrentSession);
            this.Controls.Add(this.txtBridgeVersion);
            this.Controls.Add(this.txtCurrentPath);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "CenposQA";
            this.Text = "SQA Assistant - CenPOS";
            this.Load += new System.EventHandler(this.CenposQA_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnRunBridgeProd;
        private System.Windows.Forms.Button btnStoreSession;
        private System.Windows.Forms.Button btnClearSession;
        private System.Windows.Forms.Button btnRunWsQa;
        private System.Windows.Forms.Button btnRunBridgeQa;
        private System.Windows.Forms.Button btnLoadWs;
        private System.Windows.Forms.Button btnLoadBridgeQa;
        private System.Windows.Forms.Button btnRunWsProd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtCurrentPath;
        private System.Windows.Forms.TextBox txtBridgeVersion;
        private System.Windows.Forms.TextBox txtCurrentSession;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label lblVersion;
    }
}

